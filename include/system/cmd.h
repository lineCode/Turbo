#ifndef TURBO_CMD_H
#define TURBO_CMD_H

#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "system/system_def.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class CMDParser
        {
        private:
            int argc = 0;
            char ** argv = nullptr;
            std::string trace = "";
            Uint8 largest_option = 0;
            Uint8 largest_params = 0;
            std::map<std::string, std::vector<std::string>> args;
            std::map<std::string, std::vector<Uint8>> options;
            std::map<std::string, std::string> option_info;

        public:
            explicit CMDParser(int argc, char ** argv);
            bool checkArgs();
            void setOption(std::string option, Uint8 params = 0, bool required = false, std::string info = "");
            std::vector<std::string> getOption(std::string option);
            bool isSet(std::string option);
            std::string getTrace();
            void printTrace();
            std::string getHelp();
            void printHelp();
        };
    }
}

#endif //TURBO_CMD_H