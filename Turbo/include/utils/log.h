#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

/**
*** @package 	log
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief
***
***
**/

#include "utils/utils.h"
#include "extern/time.h"

using EXTERN::Timer;

namespace UTILS
{
    /**
    *** @class Log
    ***
    ***
    **/
    class Log
    {
    public:
        static void log(std::string tag, const std::string message, LOG_TYPE type);
        static void warning(std::string tag, const std::string message, LOG_TYPE type);
        static void error(std::string tag, const std::string message, LOG_TYPE type);
        static void info(std::string tag, const std::string message, LOG_TYPE type);
        static void debug(std::string tag, const std::string message, LOG_TYPE type);
        static void console(std::string tag, const std::string message, LOG_TYPE type);
        static void clear(std::string filename);
    };
}

#endif // LOG_H_INCLUDED
