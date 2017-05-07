#include "extern/extern.h"

using namespace EXTERN;

string INI::getValue(string key)
{
	return this->kvp[""][key];
}

string INI::getValue(string caption, string key)
{
	return this->kvp[caption][key];
}

int INI::getValueAsInt(string key)
{
	return stoi(this->kvp[""][key]);
}

int INI::getValueAsInt(string caption, string key)
{
	return stoi(this->kvp[caption][key]);
}

float INI::getValueAsFloat(string key)
{
	return stof(this->kvp[""][key]);
}

float INI::getValueAsFloat(string caption, string key)
{
	return stof(this->kvp[caption][key]);
}

void INI::setValue(string key, string value)
{
	this->kvp[""][key] = value;
}

void INI::setValue(string caption, string key, string value)
{
	this->kvp[caption][key] = value;
}

bool INI::isEmpty()
{
	if(this->kvp.size() == 0)
	{
		return true;
	}
	return false;
}

XML::XML()
{

}

XML::XML(string tag, bool line_tag)
{
	this->tag = tag;
	this->line_tag = line_tag;
	this->multi_tag = !line_tag;
}

string XML::getValue(string key)
{
	return this->kvp[key];
}

int XML::getValueAsInt(string key)
{
	return atoi(this->kvp[key].c_str());
}

float XML::getValueAsFloat(string key)
{
    return stof(this->kvp[key]);
}

void XML::setValue(string key, string value)
{
	this->kvp[key] = value;
}

XML XML::findTag(string tag)
{
	XML result;
	if(this->tag == tag)
	{
		result = *this;
	}
	else if(this->children.size() > 0)
	{
		for(XML * child : this->children)
		{
			if(child->tag == tag)
			{
				result = *child;
				break;
			}
		}
		if(result.isEmpty())
		{
			for(XML * child : this->children)
			{
				if(result.isEmpty())
				{
					result = child->findTag(tag);
				}
				else
				{
					break;
				}
			}
		}
	}
	else if(this->next != nullptr)
	{
		result = this->next->findTag(tag);
	}
	return result;
}

bool XML::isEmpty()
{
	bool success = false;

	if(this->tag == "" && this->content == "" &&
	   this->kvp.size() == 0 && this->children.size() == 0 &&
	   this->prev == nullptr && this->next == nullptr &&
	   this->parent == nullptr && this->next == nullptr)
	{
		success = true;
	}
	return success;
}

void XML::printXML()
{
	cout << this->tag << "\n";
	for(auto & kvp : this->kvp)
	{
		cout << "  -> " << kvp.first << " = " << kvp.second << "\n";
	}
	cout << "  -> \"" << this->content << "\"" << endl;
	if(this->child != nullptr)
	{
		this->child->printXML();
	}
}

/*TODO
XML::~XML()
{
    if(this->children.size() != 0)
    {
        for(XML * child : this->children)
        {
            child->~XML();
        }
    }
}*/