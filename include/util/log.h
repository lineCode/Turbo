#ifndef TURBO_LOG_H
#define TURBO_LOG_H

#include <iostream>

#include <SDL_types.h>

#include "system/time.h"

namespace TURBO
{
    namespace UTIL
    {
        enum LOG_FORMAT : Uint8
        {
            DEFAULT         = 0,
            BOLD_ON         = 1,
            UNDERLINED_ON   = 4,
            INVERSE_ON      = 7,
            BOLD_OFF        = 21,
            UNDERLINE_OFF   = 24,
            INVERSE_OFF     = 27,
            FG_RED          = 31,
            FG_GREEN        = 32,
            FG_BLUE         = 34,
            FG_DEFAULT      = 39,
            BG_RED          = 41,
            BG_GREEN        = 42,
            BG_BLUE         = 44,
            BG_DEFAULT      = 49
        };

        enum class LOG_MODE : Uint8
        {
            LOG_NOTHING = 0x0,
            LOG_INFO    = 0x1,
            LOG_WARNING = 0x2,
            LOG_ERROR   = 0x3,
            LOG_DEBUG   = 0x4,
            LOG_VERBOSE = 0x5,
        };

        class Log
        {
        public:
            Log() = delete;
            Log(Log & other) = delete;
            Log(Log && other) = delete;
            void operator=(Log & other) = delete;
            static LOG_MODE                 log_mode;
            static LOG_MODE setLogMode(LOG_MODE new_mode);
            static LOG_MODE getLogMode();
            static void log(const std::string & message, LOG_MODE mode);
            static void clearLine();
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
