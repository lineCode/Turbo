#include "util/json.h"

namespace TURBO
{
    namespace UTIL
    {
        JSONParser::JSONParser(const std::string file)
            : buffer(BUFFER_SIZE)
        {
            json = read(file);
        }

        JSON JSONParser::getJSON()
        {
            return json;
        }

        JSON JSONParser::read(const std::string file)
        {
            JSON head;
            head.key = "asd";

            std::ifstream in(file, std::ios::binary | std::ios::ate);
            file_size = in.tellg();
            in.seekg(std::ios::beg);

            std::cout << "file size " << file_size << std::endl;

            if(file_size > 0)
            {
                in.read(buffer.data(), BUFFER_SIZE);
                buffer_pos = buffer.begin();

                while(file_pos < file_size - 1)
                {
                    try
                    {
                        if(!readObject() && !readArray())
                        {

                        }
                    }
                    catch(std::exception & ex)
                    {
                        std::cout << "exception while reading" << std::endl;
                    }

                    if (std::distance(buffer.begin(), buffer_pos) > BUFFER_SIZE - BUFFER_REFILL_SIZE)
                    {
                        std::cout << "fill buffer " << std::endl;
                        std::vector<char> temp(BUFFER_SIZE);
                        in.read(temp.data(), BUFFER_SIZE);
                        temp.insert(temp.begin(), buffer_pos, buffer.end());
                        buffer = temp;
                        buffer_pos = buffer.begin();
                    }
                }
            }
            in.close();
            return head;
        }

        int JSONParser::skipWhitespaces()
        {
            int skipped = 0;
            while(Parser::isWhitespaceChar(*buffer_pos))
            {
                buffer_pos++;
                file_pos++;
            }
            return skipped;
        }

        bool JSONParser::readKey()
        {
            bool string_quotes = Parser::isQuoteChar(*buffer_pos);
            std::string key;

            if(string_quotes)
            {
                buffer_pos++;
                file_pos++;
                while(Parser::isIdentifierChar(*buffer_pos) || Parser::isSpaceChar(*buffer_pos))
                {
                    key += *buffer_pos;
                    buffer_pos++;
                    file_pos++;
                }

                if(!Parser::isQuoteChar(*buffer_pos))
                {
                    return false;
                }

                buffer_pos++;
                file_pos++;
                return true;
            }
            else
            {
                while(Parser::isIdentifierChar(*buffer_pos))
                {
                    key += *buffer_pos;
                    buffer_pos++;
                    file_pos++;
                }
            }

            tokens.push(key);
            return true;
        }

        bool JSONParser::readValue()
        {
            bool string_quotes = Parser::isQuoteChar(*buffer_pos);
            std::string value;

            if(string_quotes)
            {
                buffer_pos++;
                file_pos++;
                while(Parser::isAlphabeticChar(*buffer_pos)
                      || Parser::isSpaceChar(*buffer_pos)
                      || Parser::isNumericChar(*buffer_pos))
                {
                    value += *buffer_pos;
                    buffer_pos++;
                    file_pos++;
                }

                if(!Parser::isQuoteChar(*buffer_pos))
                {
                    return false;
                }

                buffer_pos++;
                file_pos++;
                return true;
            }
            else
            {
                while(Parser::isIdentifierChar(*buffer_pos))
                {
                    value += *buffer_pos;
                    buffer_pos++;
                    file_pos++;
                }
            }

            tokens.push(value);
            return true;
        }

        bool JSONParser::readArray()
        {
            skipWhitespaces();

            if(!Parser::isSquareBracketOpenChar(*buffer_pos))
            {
                return false;
            }
            buffer_pos++;
            file_pos++;

            while(readValue())
            {
                skipWhitespaces();
                if(Parser::isCommaChar(*buffer_pos))
                {
                    buffer_pos++;
                    file_pos++;
                }
            }

            if(!Parser::isSquareBracketCloseChar(*buffer_pos))
            {
                return false;
            }
            buffer_pos++;
            file_pos++;

            return true;
        }

        bool JSONParser::readObject()
        {
            skipWhitespaces();

            if(!Parser::isCurlyBracketOpenChar(*buffer_pos))
            {
                return false;
            }

            buffer_pos++;
            file_pos++;

            if(readKey())
            {
                if(!(readArray() || readValue() || readArray()))
                {
                    // no value
                    return false;
                }
            }
            else
            {
                // no key
                return false;
            }

            skipWhitespaces();

            if(!Parser::isCurlyBracketCloseChar(*buffer_pos))
            {
                return false;
            }

            buffer_pos++;
            file_pos++;

            return true;
        }
    }
}