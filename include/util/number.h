#ifndef TURBO_NUMBER_H
#define TURBO_NUMBER_H

#include <sstream>

#include "util/util_def.h"

namespace TURBO
{
    namespace UTIL
    {
        unsigned                    digits(long number);
        unsigned                    toNumber(std::string number);
    }
}

#endif //TURBO_NUMBER_H
