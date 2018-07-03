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
                std::cout << prefix << "+---------------" << "\n";
                std::cout << prefix << "|Tagname: " << tag << "\n";
                std::cout << prefix << "|Attributes: " << "\n";
                for(auto &entry : kvp)
                {
                    std::cout << prefix << "|  " << entry.first << " = " << entry.second << "\n";
                }
                if(!content.empty())
                {
                    std::cout << prefix << "|Content: " << "\n";
                    std::cout << prefix << "|  \"" << content << "\"" << "\n";
                }
                std::cout << prefix << "+---------------" << "\n";
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

        bool XMLParser::isNameStartChar(char c)
        {
            // : , _ , A-Z , a-z
            return c == 0x3A || c == 0x5F || (c >= 0x41 && c <= 0x5A) || (c >= 0x61 && c <= 0x7A);
        }

        bool XMLParser::isNameChar(char c)
        {
            // - , . , · , : , _ , A-Z , a-z , 0-9
            return c == 0x2D || c == 0x2E || c == 0xB7 || isNameStartChar(c) || (c >= 0x30 && c <= 0x39);
        }

        int XMLParser::skipSpaces()
        {
            int skipped = 0;
            while(Parser::isSpaceChar(*buffer_pos))
            {
                skipped++;
                buffer_pos++;
                buffer_offset++;
            }
            return skipped;
        }

        int XMLParser::skipWhiteSpaces()
        {
            int skipped = 0;
            while(Parser::isWhitespaceChar(*buffer_pos))
            {
                skipped++;
                buffer_pos++;
                buffer_offset++;
            }
            return skipped;
        }
        
        bool XMLParser::readComment()
        {
//            std::cout << "readComm" << "\n";
            while(*buffer_pos)
            {
                if(Parser::isMinusChar(*buffer_pos))
                {
                    buffer_pos++;
                    buffer_offset++;
                    
                    if(Parser::isMinusChar(*buffer_pos))
                    {
                        buffer_pos++;
                        buffer_offset++;
                        
                        if(Parser::isGTChar(*buffer_pos))
                        {
                            // Comment End
                            buffer_pos++;
                            buffer_offset++;
                            return true;
                        }
                    }
                }
                buffer_pos++;
                buffer_offset++;
            }
            return false;
        }

        bool XMLParser::readName()
        {
//            std::cout << "readName" << "\n";
            skipWhiteSpaces();

            std::string name;
            if(!isNameStartChar(*buffer_pos))
            {
                // name contains illegal chars
                return false;
            }

            name += *buffer_pos;
            buffer_pos++;
            buffer_offset++;

            while(isNameChar(*buffer_pos))
            {
                name += *buffer_pos;
                buffer_pos++;
                buffer_offset++;
            }

            if(current->tag.empty())
            {
                current->tag = name;
            }
            else
            {
                if(name == current->tag || current->line_tag)
                {
                    current->tag = "";
                }
                else
                {
                    return false;
                }
            }

            return true;
        }

        bool XMLParser::readAttribute()
        {
//            std::cout << "readAtt" << "\n";
            std::string key;
            std::string value;

            skipWhiteSpaces();

            while(isNameChar(*buffer_pos))
            {
                key += *buffer_pos;
                buffer_pos++;
                buffer_offset++;
            }

            if(Parser::isEqualChar(*buffer_pos))
            {
                buffer_pos++;
                buffer_offset++;

                if (!Parser::isQuoteChar(*buffer_pos))
                {
                    // missing quote
                    return false;
                }

                buffer_pos++;
                buffer_offset++;

                while(isNameChar(*buffer_pos))
                {
                    value += *buffer_pos;
                    buffer_pos++;
                    buffer_offset++;
                }

                if (!Parser::isQuoteChar(*buffer_pos))
                {
                    // missing quote
                    return false;
                }

                buffer_pos++;
                buffer_offset++;
            }

            if(!key.empty())
            {
                current->kvp[key] = value;
                return true;
            }

            return false;
        }

        bool XMLParser::readTag()
        {
//            std::cout << "readTag" << "\n";
            skipWhiteSpaces();

            if(!Parser::isLTChar(*buffer_pos))
            {
                // text
                std::string text;
                while(!Parser::isLTChar(*buffer_pos))
                {
                    buffer_pos++;
                    buffer_offset++;
                }
                current->content = text;
                return true;
            }

            buffer_pos++;

            if(Parser::isExclamationChar(*buffer_pos))
            {
                buffer_pos++;
                buffer_offset++;
                
                if(Parser::isMinusChar(*buffer_pos))
                {
                    if(Parser::isMinusChar(*buffer_pos))
                    {
                        buffer_pos += 2;
                        buffer_offset += 2;
                        return readComment();
                    }
                }
                else
                {
                    // CDATA or other
                    // not supported
                    // no correct comment
                    return false;
                }
            }
            else if(Parser::isSlashChar(*buffer_pos))
            {
                buffer_pos++;
                buffer_offset++;

                if(!readName())
                {
                    // end tag does not correspond to start tag
                    return false;
                }

                skipWhiteSpaces();

                if(!Parser::isGTChar(*buffer_pos))
                {
                    return false;
                }

                buffer_pos++;
                buffer_offset++;
                last = current;
//                current = new XML;
//
//                last->next = current;
//                current->prev = last;
                return true;
            }

            if(Parser::isQuestionChar(*buffer_pos))
            {
                // Head Tag
                current->head = true;
                buffer_pos++;
                buffer_offset++;
            }

            if(!readName())
            {
                // no tag
                return false;
            }

            skipWhiteSpaces();

            while(readAttribute())
            {

            }

            skipWhiteSpaces();

            if(Parser::isGTChar(*buffer_pos))
            {
                // Start Tag
                buffer_pos++;
                buffer_offset++;
            }
            else if(Parser::isQuestionChar(*buffer_pos) || Parser::isSlashChar(*buffer_pos))
            {
                buffer_pos++;
                buffer_offset++;

                skipWhiteSpaces();

                if(Parser::isGTChar(*buffer_pos))
                {
                    // Line Tag
                    buffer_pos++;
                    buffer_offset++;
                    last = current;
                    current->line_tag = true;
//                    current = new XML;
                }
                else
                {
                    // no correct line end tag
                    return false;
                }
            }
            else
            {
                // no correct line end tag
                return false;
            }
            return true;
        }

        bool XMLParser::fillBuffer(std::ifstream & in)
        {
            long buffer_diff = (buffer_pos - &buffer[0]) * sizeof(char);
            // refill buffer if less than refill size
            if(buffer_diff >= BUFFER_SIZE - BUFFER_REFILL_SIZE)
            {
                char new_buffer[buffer_diff];
                char temp[BUFFER_SIZE];

                // read until the new buffer plus the old buffer is equal to buffer size
                if(in.read(new_buffer, buffer_diff))
                {

                }

                // save rest from old buffer
                strncpy(temp, buffer_pos, BUFFER_SIZE - buffer_diff);

                // add new buffer
                strncpy(temp + (BUFFER_SIZE - buffer_diff), new_buffer, buffer_diff);
                std::cout << temp << "\n";

                buffer = temp;
                buffer[BUFFER_SIZE - 1] = '\0';

                buffer_pos = &buffer[0];
                return true;
            }
            return false;
        }

        XML XMLParser::read(const std::string file)
        {
            filename    = file;
            head        = new XML;
            current     = head;
            begin       = 0;
            buffer      = new char[BUFFER_SIZE];
            buffer_pos  = &buffer[0];

            std::ifstream in(file, std::ios::in);
            begin = in.tellg();
            in.seekg(0, std::ios::end);
            file_size = (in.tellg()-begin);
            in.seekg(0, std::ios::beg);

            std::cout << " size " << file_size << "\n";

            in.read(buffer, BUFFER_SIZE);

            while(buffer_offset < file_size - 1)
            {
                skipWhiteSpaces();
                if(!fillBuffer(in) && !readTag())
                {
                    // error
                    for (int i = 0; i < 10; ++i)
                        buffer_pos--;
                    for (int i = 0; i < 20; ++i)
                        std::cout << *buffer_pos++;
                    std::cout << buffer_offset << "\n";
                    Log::war("error");
                    in.close();
                    delete[] buffer;
                    free(head);
                    return xml;
                }
                std::cout << buffer_offset << "\n";
            }

            std::cout << "ebd" << "\n";
            in.close();
            xml = *head;
            delete[] buffer;
            delete head;
            return xml;
        }

        bool XMLParser::write(const std::string file, XML xml)
        {
            return writeXML(file, xml);
        }

        bool XMLParser::writeXML(std::string file, XML head, std::string prepend, std::ios::openmode flags)
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
                        out << "?>" << "\n";
                    }
                    else if(!xml->content.empty())
                    {
                        out << '>' << xml->content << "</" << xml->tag << '>' << "\n";
                    }
                    else
                    {
                        out << "/>" << "\n";
                    }
                }
                else if(!xml->line_tag)
                {
                    out << '>' << "\n";
                    if(xml->child != nullptr)
                    {
                        XML child = *xml->child;
                        success = writeXML(file, child, prepend + "    ", std::ios::app | std::ios::ate);
                    }
                    std::ofstream os(file, std::ios::app | std::ios::ate);
                    if(xml->child == nullptr)
                    {
                        os << prepend << "    " << xml->content << "\n";
                    }
                    os << prepend << "</" << xml->tag << '>' << "\n";
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