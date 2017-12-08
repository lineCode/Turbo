#ifndef TURBO_JSON_H
#define TURBO_JSON_H

#include <iostream>
#include <fstream>

namespace TURBO
{
    namespace UTIL
    {
        struct JSON
        {
            std::string key;
        };

        class JSONParser
        {
        private:
            JSON    json;
            char   *buffer_pos;

        public:
            JSONParser(std::string file);
            JSON read(std::string file);
            bool isSquareBracketOpenChar(char c);
            bool isSquareBracketCloseChar(char c);
            bool isCurlyBracketOpenChar(char c);
            bool isCurlyBracketCloseChar(char c);
            bool isWhitespaceChar(char c);
            int skipWhitespaces();
            bool readKey();
            bool readValue();
            bool readArray();
            bool readObject();
            bool readJSON();
        };
    }
}

#endif //TURBO_JSON_H
