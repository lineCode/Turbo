#include "util/log.h"

namespace TURBO
{
    namespace UTIL
    {
        typedef SYSTEM::Time Time;
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

        void Log::log(const std::string & message, const LOG_MODE mode)
        {
            if(mode <= Log::log_mode)
            {
                Log::log(message);
            }
        }

        void Log::log(const std::string & message)
        {
            std::cout << Time::getTimestampToString(Time::getTimestamp(), "%d.%m %H:%M") << " | "
                      << std::right << std::setw(12) << std::setfill(' ')
                      << Time::getTicksToString(Time::getTicks(), "%H:%M:%S.%f") << ": "
                      << message << std::endl;
        }

        void Log::info(const std::string &message)
        {
            Log::log("[INFO]" + message, LOG_MODE::LOG_INFO);
        }

        void Log::war(const std::string & message)
        {
            Log::log("[WARNING]" + message, LOG_MODE::LOG_WARNING);
        }

        void Log::err(const std::string & message)
        {
            Log::log("[ERROR]" + message, LOG_MODE::LOG_ERROR);
        }
    }
}