#ifndef TURBO_TEXT_H
#define TURBO_TEXT_H

#include "video/font.h"
#include "video/texture.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Text
        {
        private:
            Texture & texture;

        public:
            Text(std::string text, Font *font = nullptr);
            std::string setText(std::string text = "");
            std::string getText();
        };
    }
}

#endif //TURBO_TEXT_H
