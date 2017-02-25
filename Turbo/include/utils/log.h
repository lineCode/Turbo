#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

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
        static void log(std::string tag, const std::string message, TURBO::LOG_TYPE type) const;
        static void warning(std::string tag, const std::string message, TURBO::LOG_TYPE type) const;
        static void error(std::string tag, const std::string message, TURBO::LOG_TYPE type) const;
        static void info(std::string tag, const std::string message, TURBO::LOG_TYPE type) const;
        static void debug(std::string tag, const std::string message, TURBO::LOG_TYPE type) const;
        static void console(std::string tag, const std::string message, TURBO::LOG_TYPE type) const;
        static void clear(std::string filename);
    };
}

#endif // LOG_H_INCLUDED
