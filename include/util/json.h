#ifndef TURBO_JSON_H
#define TURBO_JSON_H

#include "util/util_def.h"
#include <iostream>
#include <vector>

namespace TURBO
{
    namespace UTIL
    {
        template <typename T>
        struct JSONPair<std::string, T>
        {
            std::string key;
            T value;
        };

        struct JSON
        {
            std::vector<JSONPair> kvp;
        };
    }
}

#endif //TURBO_JSON_H
