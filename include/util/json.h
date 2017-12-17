#ifndef TURBO_JSON_H
#define TURBO_JSON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "util/parser.h"

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
            JSON json;
            std::stack<std::string> tokens;
            std::vector<char> buffer;
            std::vector<char>::iterator buffer_pos;
            unsigned long file_pos = 0;
            std::streamsize file_size;

        public:
            explicit JSONParser(std::string file);
            JSON getJSON();
            JSON read(std::string file);
            int skipWhitespaces();
            bool readKey();
            bool readValue();
            bool readArray();
            bool readObject();
        };
    }
}

#endif //TURBO_JSON_H
