#ifndef TURBO_XML_H
#define TURBO_XML_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

#include <regex>

#include "util/util_def.h"
#include "util/string.h"
#include "util/log.h"
#include "util/parser.h"

namespace TURBO
{
    namespace UTIL
    {
        enum XML_TOKEN
        {
            INVALID = 0,
            DOCUMENT_START = 1,
            COMMENT_START = 2,
            TAG_START = 3,
            ATTRIBUTE_START = 4
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
            std::streamsize         file_size;
            XML 					xml;
            XML                    *head;
            XML                    *current;
            XML                    *last;
            XML_TOKEN               token = XML_TOKEN::DOCUMENT_START;
            char                   *buffer_pos;
            long                    begin = 0;
            long                    buffer_offset = 0;
            char                   *buffer;

            bool                    isNameStartChar(char c);
            bool                    isNameChar(char c);
            int                     skipSpaces();
            int                     skipWhiteSpaces();
            bool                    readComment();
            bool                    readName();
            bool                    readAttribute();
            bool                    readTag();
            bool                    fillBuffer(std::ifstream &in);
            bool 					writeXML(std::string file, XML xml, std::string prepend = "",
                                             std::ios::openmode flags = std::ios::out | std::ios::trunc);
            void                    free(XML * xml);

        public:
            explicit XMLParser(std::string file);
            XML 					read(std::string file = "");
            bool                    write(std::string file, XML xml);
            XML						getXML();
        };
    }
}

#endif //TURBO_XML_H
