#include "gui/units.h"

namespace TURBO
{
    namespace GUI
    {
        //          px        mm        cm        pt        pc        in
        // 1 px     1         127/480   127/4800  4/3       16        1/96              * relative to the display size
        // 1 mm               1         0.1
        // 1 cm               10        1
        // 1 pt     3/4                           1                   1/72
        // 1 pc               4.233     0.4233    12        1         0.166665
        // 1 in     96        25.4      2.54      72                  1

        long double operator ""_px(unsigned long long size)
        {
            return size;
        }

        long double operator ""_px(long double size)
        {
            return size;
        }

        long double operator ""_mm(unsigned long long size)
        {
            return size * PX_TO_MM;
        }

        long double operator ""_mm(long double size)
        {
            return size * PX_TO_MM;
        }

        long double operator ""_cm(unsigned long long size)
        {
            return size * PX_TO_CM;
        }

        long double operator ""_cm(long double size)
        {
            return size * PX_TO_CM;
        }

        long double operator ""_pt(unsigned long long size)
        {
            return size * PX_TO_PT;
        }

        long double operator ""_pt(long double size)
        {
            return size * PX_TO_PT;
        }

        long double operator ""_pc(unsigned long long size)
        {
            return size * PX_TO_PC;
        }

        long double operator ""_pc(long double size)
        {
            return size * PX_TO_PC;
        }

        long double operator ""_in(unsigned long long size)
        {
            return size * PX_TO_IN;
        }

        long double operator ""_in(long double size)
        {
            return size * PX_TO_IN;
        }
    }
}