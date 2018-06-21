#ifndef TURBO_RANGE_H
#define TURBO_RANGE_H

#include "math/math_def.h"

namespace TURBO
{
    namespace MATH
    {
        template<typename T>
        class Range
        {
        public:
            class Iterator
            {
            public:
                T v;
                T b;
                T e;
                T s;

                Iterator(T v, T b, T e, T s)
                    : v(v), b(b), e(e), s(s)
                {

                }

                T operator*() const
                {
                    return v;
                }

                operator T& ()
                {
                    return v;
                }

                Iterator &operator++()
                {
                    if(b <= e)
                    {
                        v += s;
                    }
                    else
                    {
                        v -= s;
                    }
                    return *this;
                }

                bool operator==(const T &other) const
                {
                    if(b <= e)
                    {
                        return v >= other;
                    }
                    else if(b > e)
                    {
                        return v <= other;
                    }
                }

                bool operator!=(const T &other) const
                {
                    return v != other;
                }
            };

            T b;
            T e;
            T s;

            Range(T from, T to, T step)
                : b(from), e(to), s(step)
            {

            }

            Iterator begin() const
            {
                return Iterator(b, b, e, s);
            };

            Iterator end() const
            {
                return Iterator(e, b, e, s);
            };
        };

        template <typename T>
        Range<T> range(T from, T to, T step)
        {
            return Range<T>(from, to, step);
        }
    }
}

#endif //TURBO_RANGE_H
