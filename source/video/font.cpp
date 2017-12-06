#include "video/font.h"

namespace TURBO
{
    namespace VIDEO
    {
        Font::Font(std::string filepath, Uint8 ptsize, Uint8 index)
            : SDL2pp::Font(filepath, ptsize, index), path(filepath)
        {

        }
    }
}