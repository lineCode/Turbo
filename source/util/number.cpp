#include "util/number.h"

namespace TURBO
{
    namespace UTIL
    {
        unsigned digits(long number)
        {
            return number > 0 ? static_cast<unsigned>(log10(number) + 1) : 1;
        }

        unsigned bits(long number)
        {
            unsigned bits = 0;
            while(number > 0)
            {
                number >>= 1;
                bits++;
            }
            return bits;
        }

        unsigned bitTrue(long number)
        {
            unsigned bits = 0;
            while(number > 0)
            {
                if(number & 0x1)
                {
                    bits++;
                }
                number >>= 1;
            }
            return bits;
        }

        unsigned bitsFalse(long number)
        {
            unsigned bits = 0;
            while(number > 0)
            {
                if(!(number & 0x1))
                {
                    bits++;
                }
                number >>= 1;
            }
            return bits;
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