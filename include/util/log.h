#ifndef TURBO_LOG_H
#define TURBO_LOG_H

#include <iostream>

#include <SDL_types.h>

#include "system/time.h"

namespace TURBO
{
    namespace UTIL
    {
        enum class LOG_MODE : Uint8
        {
            LOG_NOTHING = 0x0,
            LOG_INFO = 0x1,
            LOG_WARNING = 0x2,
            LOG_ERROR = 0x3,
            LOG_DEBUG = 0x4,
            LOG_VERBOSE = 0x5,
        };

        class Log
        {
        public:
            Log() = delete;
            Log(Log & other) = delete;
            Log(Log && other) = delete;
            void operator=(Log & other) = delete;
            static LOG_MODE log_mode;
            static LOG_MODE setLogMode(LOG_MODE new_mode);
            static LOG_MODE getLogMode();
            static void log(const std::string & message, LOG_MODE mode);
            static void log(const std::string & message);
            static void info(const std::string & message);
            static void war(const std::string & message);
            static void err(const std::string & message);
        };

        #define LOG(message) TURBO::UTIL::Log::log(message)
        #define INF(message) TURBO::UTIL::Log::info(message)
        #define WAR(message) TURBO::UTIL::Log::war(message)
        #define ERR(message) TURBO::UTIL::Log::err(message)
    }
}

#endif //TURBO_LOG_H
