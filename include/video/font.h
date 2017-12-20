#ifndef TURBO_FONT_H
#define TURBO_FONT_H

#include <SDL_ttf.h>

#include "video/video_def.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Font
        {
        private:
            TTF_Font * font;
            std::string path;

        public:
            Font(std::string path, Uint8 ptsize, Uint8 index = 0);
            ~Font();
            TTF_Font * getFont();
        };
    }
}

#endif //TURBO_FONT_H
