#ifndef TURBO_UNITS_H
#define TURBO_UNITS_H

#include "gui/gui_def.h"

namespace TURBO
{
    namespace GUI
    {
        const double PX_TO_MM = 127/480;
        const double PX_TO_CM = 127/4800;
        const double PX_TO_PT = 4/3;
        const double PX_TO_PC = 16;
        const double PX_TO_IN = 1/96;

        const double PT_TO_PX = 3/4;
        const double PT_TO_IN = 1/72;

        const double IN_TO_PX = 96;
        const double IN_TO_MM = 25.4;
        const double IN_TO_CM = 2.54;
        const double IN_TO_PT = 72;

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
