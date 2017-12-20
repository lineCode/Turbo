#include "video/font.h"

namespace TURBO
{
    namespace VIDEO
    {
        Font::Font(std::string filepath, Uint8 ptsize, Uint8 index)
        {
            font = TTF_OpenFont(path.c_str(), ptsize);
        }

        Font::~Font()
        {
            TTF_CloseFont(font);
        }

        TTF_Font * Font::getFont()
        {
            return font;
        }
    }
}