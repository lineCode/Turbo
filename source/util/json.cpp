#include "util/json.h"

namespace TURBO
{
    namespace UTIL
    {
        JSONParser::JSONParser(std::string file)
        {
            json = read(file);
        }

        JSON JSONParser::read(std::string file)
        {
            long begin = 0;

            std::fstream in(file, std::ios::in);
            begin = in.tellg();
            in.seekg(std::ios::end);
            std::streamsize file_size = (in.tellg()-begin);
            in.seekg(std::ios::beg);

            while(readJSON())
            {

            }
        }

        bool JSONParser::isCurlyBracketOpenChar(char c)
        {
            return c == 0x7B;
        }

        bool JSONParser::isCurlyBracketCloseChar(char c)
        {
            return c == 0x7D;
        }

        bool JSONParser::isSquareBracketOpenChar(char c)
        {
            return c == 0x5B;
        }

        bool JSONParser::isSquareBracketCloseChar(char c)
        {
            return c == 0x5D;
        }

        bool JSONParser::isWhitespaceChar(char c)
        {
            return c == 0x20 || c == 0x0A;
        }

        int JSONParser::skipWhitespaces()
        {
            int skipped = 0;
            while(isWhitespaceChar(*buffer_pos))
            {
                buffer_pos++;
            }
            return skipped;
        }

        bool JSONParser::readArray()
        {
            skipWhitespaces();

            if(!isSquareBracketOpenChar(*buffer_pos))
            {
                return false;
            }

            buffer_pos++;

            while(!isSquareBracketCloseChar(*buffer_pos))
            {

            }

            return true;
        }

        bool JSONParser::readObject()
        {
            skipWhitespaces();

            if(!isCurlyBracketOpenChar(*buffer_pos))
            {
                return false;
            }

            buffer_pos++;

            if(readKey())
            {
                if(!(readArray() || readValue()))
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

            if(!isCurlyBracketCloseChar(*buffer_pos))
            {
                return false;
            }

            buffer_pos++;

            return true;
        }

        bool JSONParser::readJSON()
        {
            skipWhitespaces();

            if(isCurlyBracketCloseChar(*buffer_pos))
            {
                buffer_pos++;
            }
            else if(isSquareBracketOpenChar(*buffer_pos))
            {
                buffer_pos++;
            }
            else
            {
                // error
            }

            skipWhitespaces();

            if(readArray())
            {

            }

            return false;
        }
    }
}