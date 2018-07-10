#ifndef TURBO_LOG_H
#define TURBO_LOG_H

#include <iostream>

#include <SDL_types.h>

#include "system/time.h"

namespace TURBO
{
    namespace UTIL
    {
        enum LOG_FORMAT
            : Uint8
        {
            DEFAULT          = 0,
            BOLD_ON          = 1,
            UNDERLINED_ON    = 4,
            BLINK_ON         = 5,
            INVERSE_ON       = 7,
            BOLD_OFF         = 21,
            UNDERLINE_OFF    = 24,
            BLINK_OFF        = 25,
            INVERSE_OFF      = 27,
            FG_BLACK         = 30,
            FG_RED           = 31,
            FG_GREEN         = 32,
            FG_YELLOW        = 33,
            FG_BLUE          = 34,
            FG_MAGENTA       = 35,
            FG_CYAN          = 36,
            FG_LIGHT_GRAY    = 37,
            FG_DEFAULT       = 39,
            BG_BLACK         = 40,
            BG_RED           = 41,
            BG_GREEN         = 42,
            BG_YELLOW        = 43,
            BG_BLUE          = 44,
            BG_MAGENTA       = 45,
            BG_CYAN          = 46,
            BG_LIGHT_GRAY    = 47,
            BG_DEFAULT       = 49,
            FG_DARK_GRAY     = 90,
            FG_LIGHT_RED     = 91,
            FG_LIGHT_GREEN   = 92,
            FG_LIGHT_YELLOW  = 93,
            FG_LIGHT_BLUE    = 94,
            FG_LIGHT_MAGENTA = 95,
            FG_LIGHT_CYAN    = 96,
            FG_WHITE         = 97,
            BG_DARK_GRAY     = 100,
            BG_LIGHT_RED     = 101,
            BG_LIGHT_GREEN   = 102,
            BG_LIGHT_YELLOW  = 103,
            BG_LIGHT_BLUE    = 104,
            BG_LIGHT_MAGENTA = 105,
            BG_LIGHT_CYAN    = 106,
            BG_WHITE         = 107
        };

        enum class LOG_MODE
            : Uint8
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

            Log(Log &other) = delete;

            Log(Log &&other) = delete;

            void operator=(Log &other) = delete;

            static LOG_MODE log_mode;

            static LOG_MODE setLogMode(LOG_MODE new_mode);

            static LOG_MODE getLogMode();

            static void clearFormat();

            static void startFormat(LOG_FORMAT format);

            static std::string format(LOG_FORMAT format, std::string message);

            static std::string format(std::vector<LOG_FORMAT> formats, std::string message);

            static void clearLine();

            static void log(const std::string & message, const LOG_MODE mode)
            {
                if(mode <= Log::log_mode)
                {
                    Log::log(message);
                }
            }

            template<typename T>
            static void log(const T &message)
            {
                std::cout << SYSTEM::Clock::getTimestampToString(SYSTEM::Clock::getTimestamp(), "%d.%m %H:%M") << " | "
                          << std::right << std::setw(12) << std::setfill(' ')
                          << SYSTEM::Clock::getTicksToString(SYSTEM::Clock::getTicks(), "%H:%M:%S.%f") << ": "
                          << message << "\n";
            }

            template<typename T>
            static void info(const T &message)
            {
                std::stringstream ss;
                ss << "\033[1;36m[INFO] " << message << "\033[0m";
                Log::log(ss.str(), LOG_MODE::LOG_INFO);
            }

            template<typename T>
            static void war(const T &message)
            {
                std::stringstream ss;
                ss << "\033[1;33m[WARNING] " << message << "\033[0m";
                Log::log(ss.str(), LOG_MODE::LOG_WARNING);
            }

            template<typename T>
            static void err(const T &message)
            {
                std::stringstream ss;
                ss << "\033[1;31m[ERROR] " << message << "\033[0m";
                Log::log(ss.str(), LOG_MODE::LOG_ERROR);
            }
        };

#define LOG(message) TURBO::UTIL::Log::log(message)
#define INF(message) TURBO::UTIL::Log::info(message)
#define WAR(message) TURBO::UTIL::Log::war(message)
#define ERR(message) TURBO::UTIL::Log::err(message)
    }
}

#endif //TURBO_LOG_H
