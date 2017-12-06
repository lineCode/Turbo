#ifndef TURBO_FONT_H
#define TURBO_FONT_H

#include <SDL2pp/Font.hh>

#include "video/video_def.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Font : public SDL2pp::Font
        {
        private:
            std::string path;

        public:
            Font(std::string path, Uint8 ptsize, Uint8 index = 0);
        };
    }
}

#endif //TURBO_FONT_H
