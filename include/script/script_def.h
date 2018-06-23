#ifndef TURBO_SCRIPT_DEF_H_H
#define TURBO_SCRIPT_DEF_H_H

#include "turbo_def.h"

#define NAME(...) #__VA_ARGS__
#define VALUE(...) __VA_ARGS__
#define CONCAT(...) __VA_ARGS__
#define CONCAT2(first, second) first ## second
#define CONCAT2S(first, second) CONCAT2(first, ) ## second

namespace TURBO
{
    namespace SCRIPT
    {

    }
}

#endif //TURBO_SCRIPT_DEF_H_H
