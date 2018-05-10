#ifndef TURBO_STRING_H
#define TURBO_STRING_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "util/util.h"

namespace TURBO
{
    namespace UTIL
    {
        std::string                 toUnicode(Uint16 code);
        std::string                 trim(const std::string & str, const std::string & whitespace = " \t");
        std::string                 toLower(std::string haystack);
        std::vector<std::string>    explode(std::string haystack, char needle);
        std::string                 implode(std::vector<std::string> haystack, std::string needle);
        std::string                 replace(std::string haystack, char needle, char replace);
        std::string                 removeSpaces(std::string haystack);
    }
}

#endif //TURBO_STRING_H
