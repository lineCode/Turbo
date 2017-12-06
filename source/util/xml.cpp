#include <iomanip>
#include "util/xml.h"

namespace TURBO
{
    namespace UTIL
    {
        XML::XML(const std::string tag, bool line_tag)
            : tag(tag), line_tag(line_tag)
        {

        }

        std::string XML::getValue(const std::string key)
        {
            return kvp[key];
        }

        int XML::getValueAsInt(const std::string key)
        {
            return atoi(kvp[key].c_str());
        }

        float XML::getValueAsFloat(const std::string key)
        {
            return stof(kvp[key]);
        }

        void XML::setValue(const std::string key, const std::string value)
        {
            kvp[key] = value;
        }

        XML XML::findTag(std::string tag)
        {
            XML result;
            if(this->tag == tag)
            {
                result = *this;
            }
            else if(children.empty())
            {
                for(XML * child : children)
                {
                    if(child->tag == tag)
                    {
                        result = *child;
                        break;
                    }
                }
                if(result.isEmpty())
                {
                    for(XML * child : children)
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
            else if(next != nullptr)
            {
                result = next->findTag(tag);
            }
            return result;
        }

        bool XML::isEmpty()
        {
            bool success = false;

            if(tag.empty() && content.empty() && kvp.empty() && children.empty() &&
               prev == nullptr && next == nullptr && parent == nullptr && next == nullptr)
            {
                success = true;
            }
            return success;
        }

        bool XML::isHead()
        {
            return head;
        }

        void XML::clear()
        {
            parent = nullptr;
            child = nullptr;
            prev = nullptr;
            tag = "";
            content = "";
            line_tag = false;
            head = false;
            kvp.clear();
            for(XML *child : children)
            {
                child->clear();
            }
            children.clear();
            if(next != nullptr)
            {
                next->clear();
            }
        }

        void XML::printXML(std::string prefix)
        {
            if(!isEmpty())
            {
                std::cout << prefix << "+---------------" << std::endl;
                std::cout << prefix << "|Tagname: " << tag << std::endl;
                std::cout << prefix << "|Attributes: " << std::endl;
                for(auto &kvp : kvp)
                {
                    std::cout << prefix << "|  " << kvp.first << " = " << kvp.second << std::endl;
                }
                if(!content.empty())
                {
                    std::cout << prefix << "|Content: " << std::endl;
                    std::cout << prefix << "|  \"" << content << "\"" << std::endl;
                }
                std::cout << prefix << "+---------------" << std::endl;
                for(XML *child : children)
                {
                    child->printXML(prefix + "  ");
                }
                if(next != nullptr)
                {
                    next->printXML(prefix);
                }
            }
        }

        XML::~XML()
        {
            if(!children.empty())
            {
                for(XML * child : children)
                {
                    child->~XML();
                }
            }
        }

        XMLParser::XMLParser(const std::string file)
            : filename(file)
        {
            xml = read(file);
        }

        XML XMLParser::read(const std::string file)
        {
            filename = file;
            head = new XML;
            long begin,end;
            std::ifstream in(file, std::ios::in);
            begin = in.tellg();
            in.seekg (0, std::ios::end);
            end = in.tellg();
            std::streamsize file_size = (end-begin);
            std::cout << file_size << std::endl;

            int max_buffer = 4096;
            std::vector<char> buffer;

            if(file_size < max_buffer)
            {
                in.read(buffer.data(), file_size);
                parseBuffer(buffer);
                std::cout << "first" << std::endl;
            }
            else
            {
                while(in.read(buffer.data(), max_buffer))
                {
                    parseBuffer(buffer);
                    std::cout << "second" << std::endl;
                }
            }

            in.close();

            xml = *head;
            free(head);
            return xml;
        }

        void XMLParser::parseBuffer(std::vector<char> buffer)
        {
            std::vector<char> target{'<', '!', '-', '-'};
            std::search(buffer.begin(), buffer.end(), target.begin(), target.end());
            reading_offset += 4096;
        }

        bool XMLParser::write(std::string file, XML head, std::string prepend, std::ios::openmode flags)
        {
            bool success = false;
            std::ofstream out(file, flags);

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
                        out << "?>" << std::endl;
                    }
                    else if(!xml->content.empty())
                    {
                        out << '>' << xml->content << "</" << xml->tag << '>' << std::endl;
                    }
                    else
                    {
                        out << "/>" << std::endl;
                    }
                }
                else if(!xml->line_tag)
                {
                    out << '>' << std::endl;
                    if(xml->child != nullptr)
                    {
                        XML child = *xml->child;
                        success = write(file, child, prepend + "    ", std::ios::app | std::ios::ate);
                    }
                    std::ofstream os(file, std::ios::app | std::ios::ate);
                    if(xml->child == nullptr)
                    {
                        os << prepend << "    " << xml->content << std::endl;
                    }
                    os << prepend << "</" << xml->tag << '>' << std::endl;
                    os.close();
                }
                xml = xml->next;
            }

            return success;
        }

        void XMLParser::free(XML * xml)
        {
            for(XML * child : xml->children)
            {
                free(child);
            }
            delete xml;
        }

        XML XMLParser::getXML()
        {
            return xml;
        }
    }
}