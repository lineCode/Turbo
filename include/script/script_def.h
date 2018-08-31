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
        template <typename T1, typename T2>
        struct offset_of_impl {
            static T2 object;
            static constexpr size_t offset(T1 T2::*member) {
                return size_t(&(offset_of_impl<T1, T2>::object.*member)) -
                       size_t(&offset_of_impl<T1, T2>::object);
            }
        };
        template <typename T1, typename T2>
        T2 offset_of_impl<T1, T2>::object;

        template <typename T1, typename T2>
        inline constexpr size_t offset_of(T1 T2::*member) {
            return offset_of_impl<T1, T2>::offset(member);
        }
    }
}

#endif //TURBO_SCRIPT_DEF_H_H
