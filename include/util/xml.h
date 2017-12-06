#ifndef TURBO_XML_H
#define TURBO_XML_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

#include "util/util_def.h"
#include "util/string.h"
#include "util/log.h"

namespace TURBO
{
    namespace UTIL
    {
        enum XML_TOKEN
        {
            INVALID = 1,
            COMMENT_START = 2,
            TAG_START = 3,
            TAG_OPEN = 5,
            TAG_CLOSE = 6,
            TAG_RESET = 7
        };

        struct XML
        {
            XML 			   *parent      = nullptr;
            XML 			   *child       = nullptr;
            XML				   *next        = nullptr;
            XML				   *prev        = nullptr;
            std::string 		tag         = "";
            std::string 		content     = "";
            bool 				line_tag    = false;
            bool				head        = false;
            std::vector<XML *> 	children;
            std::map<std::string, std::string> kvp;

            XML() = default;
            explicit XML(std::string tag, bool line_tag = false);
            std::string 		getValue(std::string key);
            int 				getValueAsInt(std::string key);
            float               getValueAsFloat(std::string key);
            void 				setValue(std::string key, std::string value);
            XML					findTag(std::string tag);
            bool 				isEmpty();
            bool                isHead();
            void                clear();
            void				printXML(std::string prefix = "  ");
            ~XML();
        };

        class XMLParser
        {
        private:
            std::string             filename;
            XML 					xml;
            XML                    *head;
            XML                    *last;
            XML                    *current;
            XML_TOKEN               last_tag = XML_TOKEN::INVALID;
            unsigned                token_pos;
            unsigned                element_pos;
            unsigned                reading_offset;
            std::stack<XML_TOKEN>   tokens;
            std::stack<std::string> tags;

        public:
            explicit XMLParser(std::string file);
            XML 					read(std::string file = "");
            void                    parseBuffer(std::vector<char> buffer);
            bool 					write(std::string file, XML xml, std::string prepend = "",
                                          std::ios::openmode flags = std::ios::out | std::ios::trunc);
            void                    free(XML * xml);
            XML						getXML();
        };
    }
}

#endif //TURBO_XML_H
