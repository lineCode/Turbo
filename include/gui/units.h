#ifndef TURBO_UNITS_H
#define TURBO_UNITS_H

#include "gui/gui_def.h"

namespace TURBO
{
    namespace GUI
    {
        long double operator""_px(unsigned long long size);
        long double operator""_px(long double size);

        long double operator""_mm(unsigned long long size);
        long double operator""_mm(long double size);

        long double operator""_cm(unsigned long long size);
        long double operator""_cm(long double size);

        long double operator""_pt(unsigned long long size);
        long double operator""_pt(long double size);

        long double operator""_pc(unsigned long long size);
        long double operator""_pc(long double size);

        long double operator""_in(unsigned long long size);
        long double operator""_in(long double size);
    }
}

#endif //TURBO_UNITS_H
