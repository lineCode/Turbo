#include "util/number.h"

namespace TURBO
{
    namespace UTIL
    {
        unsigned digits(long number)
        {
            return number > 0 ? static_cast<unsigned>(log10(number) + 1) : 1;
        }

        unsigned toNumber(const std::string number)
        {
            unsigned num = 0;
            std::stringstream ss(number);
            ss >> num;
            return num;
        }
    }
}