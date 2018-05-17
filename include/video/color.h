#ifndef TURBO_COLOR_H
#define TURBO_COLOR_H

#include "video/video_def.h"

namespace TURBO
{
    namespace VIDEO
    {

        enum COLOR
        {
            TRANSPARENT = 0x00000000,
            BLACK       = 0x000000FF,
            BLUE        = 0x0000FFFF,
            SKY         = 0x0080FFFF,
            GREEN       = 0x00FF00FF,
            MINT        = 0x00FF80FF,
            CYAN        = 0x00FFFFFF,
            GREY1       = 0x111111FF,
            GREY2       = 0x222222FF,
            GREY3       = 0x333333FF,
            GREY4       = 0x444444FF,
            GREY5       = 0x555555FF,
            GREY6       = 0x666666FF,
            GREY7       = 0x777777FF,
            PURPLE      = 0x8000FFFF,
            LIME        = 0x80FF00FF,
            GREY8       = 0x888888FF,
            GREY9       = 0x999999FF,
            GREYA       = 0xAAAAAAFF,
            GREYB       = 0xBBBBBBFF,
            GREYC       = 0xCCCCCCFF,
            GREYD       = 0xDDDDDDFF,
            GREYE       = 0xEEEEEEFF,
            RED         = 0xFF0000FF,
            MAGENTA     = 0xFF00FFFF,
            ORANGE      = 0xFF8000FF,
            YELLOW      = 0xFFFF00FF,
            WHITE       = 0xFFFFFFFF
        };

        class Color
        {
        public:
            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;

            /**
             * Creates a color.
             * @param r red
             * @param g green
             * @param b blue
             * @param a alpha
             */
            Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            /**
             * Creates a color from the bitmask of the integer.
             * @param color
             */
            Color(Uint32 color);

            SDL_Color toSDLColor();

            /**
             * Converts the values of r,g,b,a into an integer value.
             * @return Uint32
             */
            Uint32 toHexColor();
        };
    }
}

#endif //TURBO_COLOR_H
