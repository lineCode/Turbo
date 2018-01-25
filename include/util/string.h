#ifndef TURBO_STRING_H
#define TURBO_STRING_H

#include <iostream>
#include <vector>
#include <cmath>

#include "util/util.h"

namespace TURBO
{
    namespace UTIL
    {
        std::string                 trim(const std::string & str, const std::string & whitespace = " \t");
        std::string                 toLower(std::string haystack);
        std::vector<std::string>    explode(std::string haystack, char needle);
        std::string                 implode(std::vector<std::string> haystack, std::string needle);
    }
}

#endif //TURBO_STRING_H
