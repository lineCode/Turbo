#ifndef TURBO_CMD_H
#define TURBO_CMD_H

#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex>

#include "system/system_def.h"
#include "util/string.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class CMDParser
        {
        private:
            int                                                       argc           = 0;
            char                                                      **argv         = nullptr;
            std::string                                               trace          = "";
            std::string                                               app_name       = "";
            Uint8                                                     largest_option = 0;
            std::map<std::string, std::vector<std::string>>           args;
            std::map<std::string, std::map<std::string, std::string>> options;

        public:
            explicit CMDParser(int argc, char **argv);

            /**
             * Checks the validity of the given arguments.
             * @return bool depending on success
             */
            bool checkArgs();

            /**
             * Makes arguments available for the program.
             * @param short_option
             * @param long_option
             * @param params
             * @param required
             * @param defaults
             * @param info
             * @return bool depending on success
             */
            bool setOption(std::string short_option, std::string long_option, Uint8 params = 0,
                           bool required = false, std::vector<std::string> defaults = {}, std::string info = "");

            /**
             * Returns an option that was set with 'setOption'.
             * @param option
             * @return the contents of the given option
             */
            std::map<std::string, std::string> getOption(std::string option);

            /**
             * Checks if an argument was given to the program.
             * @param argument
             * @return bool
             */
            bool isSet(std::string argument);

            /**
             * Returns an argument if the program was given that argument.
             * @param argument
             * @return the parameters of the given argument
             */
            std::vector<std::string> getArgument(std::string argument);

            std::string getTrace();

            void printTrace();

            std::string getHelp();

            void printHelp();
        };
    }
}

#endif //TURBO_CMD_H