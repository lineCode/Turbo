#ifndef TURBO_INI_H
#define TURBO_INI_H

/**
 * credit to Foaly/SettingsParser @ github
 */

#include <string>
#include <map>
#include <vector>
#include <locale>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <sstream>

#include "util/util_def.h"
#include "util/string.h"

namespace TURBO
{
    namespace UTIL
    {
        struct INI
        {
            std::map<std::string, std::map<std::string, std::string>> kvp;

            std::string			getValue(std::string key, std::string caption = "");
            int 				getValueAsInt(std::string key, std::string caption = "");
            float 				getValueAsFloat(std::string key, std::string caption = "");
            void 				setValue(std::string key, std::string value, std::string caption = "");
            bool 				isEmpty();
            void                printINI();
        };

        class INIParser
        {
        private:
            std::string         filename;
            INI					ini;

        public:
            explicit INIParser(std::string file);
            INI 				read(std::string file = "");
            bool                update();
            bool 				write(const std::string & file, INI ini, std::ios::openmode flags = std::ios::out | std::ios::trunc);
            INI					getINI();
        };
    }
}

#endif //TURBO_INI_H
