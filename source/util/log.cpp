#include "util/log.h"

namespace TURBO
{
    namespace UTIL
    {
        LOG_MODE Log::log_mode = LOG_MODE::LOG_DEBUG;

        LOG_MODE Log::setLogMode(LOG_MODE new_mode)
        {
            Log::log_mode = new_mode;
            return Log::log_mode;
        }

        LOG_MODE Log::getLogMode()
        {
            return Log::log_mode;
        }

        void Log::clearFormat()
        {
            std::cout << "\033[0m";
        }

        void Log::startFormat(LOG_FORMAT format)
        {
            std::cout << "\033[" << format << "m";
        }

        std::string Log::format(LOG_FORMAT format, std::string message)
        {
            std::stringstream result;
            result << "\033[" << format << "m" << message << "\033[0m";
            return result.str();
        }

        std::string Log::format(std::vector<LOG_FORMAT> formats, std::string message)
        {
            std::stringstream result;

            result << "\033[";
            for(int index = 0; index < formats.size(); ++index)
            {
                if(index < formats.size() - 1)
                {
                    result << formats[index] << ";";
                }
                else
                {
                    result << formats[index];
                }
            }
            result << "m" << message << "\033[0m";

            return result.str();
        }

        void Log::clearLine()
        {
            std::cout << "\033[A\33[2K";
        }
    }
}