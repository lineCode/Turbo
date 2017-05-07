#include "extern/parser.h"

using namespace EXTERN;

string trim(const string & str, const string & whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if(strBegin == std::string::npos)
    {
        return "";
    }

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

INIParser::INIParser(string file, bool read) : IParser(file)
{
    if(read)
    {
		this->read(file);
    }
}

INI INIParser::read(string file)
{
    string line;
	string caption = "";
    ifstream in(file, std::ios::in);

    while(getline(in, line))
    {
		char symbol;
		string option, value;
		istringstream ss(line);

    	if(line.empty())
		{
			continue;
		}
		else
		{
			if((line.find('[') != string::npos) && (line.find(']') != string::npos))
			{
				ss >> caption;
				caption = caption.substr(1, caption.length() - 2);
				continue;
			}

			ss >> option >> symbol >> value;
			this->config.kvp[caption][option] = value;
		}
    }
	return this->config;
}

bool INIParser::write(string file, INI config, string extra, std::ios::openmode flags)
{
	bool success = false;

	ofstream out(file, flags);

	for(const auto & caption : config.kvp)
	{
		if(caption.first != "")
		{
			out << '[' << caption.first << ']' << endl;
		}
		for(const auto & kvp : caption.second)
		{
			out << kvp.first << " = " << kvp.second << "\n";
		}
		success = true;
	}
	return success;
}

INI INIParser::getINI()
{
	return this->config;
}

INIParser::~INIParser()
{

}

XMLParser::XMLParser(string file, bool read) : IParser(file)
{
	if(read)
	{
		this->xml = this->read(file);
	}
}

bool XMLParser::hasTags(string line)
{
	if(line.find('<') != string::npos && line.find('>') != string::npos)
	{
		return true;
	}
	return false;
}

bool XMLParser::isHeadTag(string line)
{
	if(line.find("<?") != string::npos && line.find("?>") != string::npos)
	{
		return true;
	}
	return false;
}

bool XMLParser::isStartTag(string line)
{
	if(!(line.find("</") != string::npos) && !(line.find("/>") != string::npos)
		&& !(this->isHeadTag(line)))
	{
		return true;
	}
	return false;
}

bool XMLParser::isEndTag(string line)
{
	if(line.find("</") != string::npos)
	{
		string::size_type pos = line.find("</");
		if(pos == 0)
		{
			return true;
		}
	}
	return false;
}

bool XMLParser::isStartEndTagLine(string line)
{
	if(line.find('>') != string::npos && line.find("</") != string::npos)
	{
		if(line.find('>') < line.find("</"))
		{
			return true;
		}
	}
	return false;
}

bool XMLParser::isTagLine(string line)
{
	if(line.find("/>") != string::npos)
	{
		string::size_type pos = line.find("/>");
		if(pos == (line.length() - 2))
		{
			return true;
		}
	}
	return false;
}

string XMLParser::capTags(string line)
{
	int tagOffset = line.find('<') + 1;
	string preTag = line.substr(tagOffset, line.find('>') - tagOffset);
	tagOffset = line.find('>') + 1;
	string content = line.substr(tagOffset, line.find("</") - tagOffset);
	tagOffset = line.find("</") + 2;
	string postTag = line.substr(tagOffset, line.find('>') - tagOffset);

	return preTag + content + postTag;
}

string XMLParser::replaceTags(string line)
{
	int tagOffset = line.find('<') + 1;
	string preTag = line.substr(tagOffset, line.find('>') - tagOffset);
	tagOffset = line.find('>') + 1;
	string content = line.substr(tagOffset, line.find("</") - tagOffset);
	tagOffset = line.find("</") + 2;
	string postTag = line.substr(tagOffset, line.find('>') - tagOffset);

	return preTag + ' ' + content + ' ' + postTag;
}

string XMLParser::parseTagName(string line)
{
	string tag = "";
	if(this->hasTags(line))
	{
		line = this->replaceTags(line);
	}
	if(line.find(' ') != string::npos)
	{
		tag = line.substr(0, line.find(' '));
	}
	else
	{
		if(isEndTag(line))
		{
			tag = line.substr(1, line.length() - 1);
		}
		else
		{
			tag = line;
		}
	}
	return tag;
}

map<string, string> XMLParser::parseKVP(string line)
{
	map<string, string> kvp;

	if(this->hasTags(line))
	{
		line = this->replaceTags(line);
	}
	while(line.find(' ') != string::npos)
	{
		string sub = line.substr(0, line.find(' '));

		if(sub.find('=') != string::npos)
		{
			string::size_type pos = sub.find('=');
			string key = sub.substr(0, pos);
			string value = sub.substr(pos + 2, sub.rfind('"') - (pos + 2));

			kvp.insert(pair<string, string>(key, value));
		}
		int subOffset = line.find(' ') + 1;
		line = line.substr(subOffset, line.length() - subOffset);
	}

	return kvp;
}

string XMLParser::parseContent(string line)
{
	int loffset = line.find('>');
	int roffset = line.find("</");
	return line.substr(loffset + 1, roffset - loffset - 1);
}

/**
* Reads a xml file.
*/
XML * XMLParser::parseFile(fstream & stream, string line)
{
	XML * first = nullptr;
	XML * current = nullptr;
	XML * xml = new XML;;

	// Read XML file line by line
	while(getline(stream, line))
	{
		line = trim(line);
		// check if line is a tag element
		if(this->hasTags(line))
		{
			// check if tag is a single line
			if(!(this->isEndTag(line) || this->isStartTag(line)))
			{
				if(this->isHeadTag(line))
				{
					xml->tag = this->parseTagName(line);
					xml->kvp = this->parseKVP(line);
					xml->line_tag = true;
					xml->head = true;
				}
				else if(this->isStartEndTagLine(line))
				{
					xml->tag = this->parseTagName(line);
					xml->kvp = this->parseKVP(line);
					xml->content = this->parseContent(line);
					xml->line_tag = true;
				}
				else if(this->isTagLine(line))
				{
					xml->tag = this->parseTagName(line);
					xml->kvp = this->parseKVP(line);
					xml->line_tag = true;
				}

				if(first == nullptr)
				{
					first = xml;
					current = first;
				}
				else
				{
					current->next = xml;
					xml->prev = current;
					current = xml;
				}
				xml = new XML;
				continue;
			}
			// tag goes over multiple lines or has children
			else
			{
				// list of children ends here
				if(this->isEndTag(line))
				{
					return first;
				}
				// element with sub tags
				else if(this->isStartTag(line))
				{
					xml->tag = this->parseTagName(line);
					xml->kvp = this->parseKVP(line);
					xml->multi_tag = true;

					// recursive call for children
					XML * firstChild = this->parseFile(stream, line);
					if(firstChild != nullptr)
					{
						if(!firstChild->line_tag && !firstChild->multi_tag)
						{
							xml->content = firstChild->content;
						}
						else
						{
							XML * child = firstChild;
							firstChild->parent = xml;
							xml->child = firstChild;

							while(child != nullptr)
							{
								xml->children.push_back(child);
								child = child->next;
							}
						}
					}
					if(first == nullptr)
					{
						first = xml;
						current = first;
					}
					else
					{
						current->next = xml;
						xml->prev = current;
						current = xml;
					}
					xml = new XML;
					continue;
				}
			}
		}
		// line is text
		else
		{
			if(first == nullptr)
			{
				first = new XML;
				first->content += line;
			}
			else
			{
				first->content += line;
			}
		}
	}
	return first;
}

XML XMLParser::read(string file)
{
    string line;
    fstream in(file, std::ios::in);

    XML * xml = this->parseFile(in, line);
    return *xml;
}

bool XMLParser::write(string file, XML head, string prepend, std::ios::openmode flags)
{
	bool success = false;
	ofstream out(file, flags);

	XML * xml = &head;

	while(xml != nullptr)
	{
		out << prepend << '<' << xml->tag;

		for(const auto & kvp : xml->kvp)
		{
			out << ' ' << kvp.first << '=' << '"' << kvp.second << '"';
		}

		if(xml->line_tag)
		{
			if(xml->head)
			{
				out << "?>" << endl;
			}
			else if(xml->content != "")
			{
				out << '>' << xml->content << "</" << xml->tag << '>' << endl;
			}
			else
			{
				out << "/>" << endl;
			}
		}
		else if(xml->multi_tag)
		{
			out << '>' << endl;
			if(xml->child != nullptr)
			{
				XML child = *xml->child;
				success = this->write(file, child, prepend + "    ",
									  std::ios::app | std::ios::ate);
			}
			ofstream out(file, std::ios::app | std::ios::ate);
			if(xml->child == nullptr)
			{
				out << prepend << "    " << xml->content << endl;
			}
			out << prepend << "</" << xml->tag << '>' << endl;
			out.close();
		}
		xml = xml->next;
	}

	return success;
}

XML XMLParser::getXML()
{
	return this->xml;
}

XMLParser::~XMLParser()
{

}