#ifndef TURBO_RENDERER_H_H
#define TURBO_RENDERER_H_H

#include "video/window.h"
#include "video/opengl.h"
#include "video/color.h"
#include "video/font.h"
#include "video/texture.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Renderer : public SDL2pp::Renderer
        {
        private:
            Window &window;
            TEXT_MODE text_mode = VIDEO::TEXT_MODE::BLENDED;
            Font * font;
            Color color_fg;
            Color color_bg;
            Color color_clear;

        public:
            Renderer(Window & window, int index, Uint32 flags);
            void clear();
            void present();
            void setFont(Font * font);
            void draw();
            void drawText(std::string text);
            void drawRect(MATH::Rect rect);
        };
    }
}

#endif //TURBO_RENDERER_H_H