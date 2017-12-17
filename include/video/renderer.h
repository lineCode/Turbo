#ifndef TURBO_RENDERER_H
#define TURBO_RENDERER_H

#include <SDL_video.h>
#include <SDL_types.h>

#include "video/video_def.h"
#include "video/window.h"
#include "video/color.h"
#include "video/font.h"
#include "gui/object.h"
#include "gui/layout.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Renderer
        {
        private:
            SDL_Renderer   *renderer;
            Window         &window;
            Font           *font;
            TEXT_MODE       text_mode;
            Color           color_fg;
            Color           color_bg;
            Color           color_text;
            Color           color_draw;
            Color           color_clear;

        public:
            Renderer(Window & window, int index, Uint32 flags);
            ~Renderer();
            SDL_Renderer * getRenderer();
            void clear();
            void present();
            Color &setDrawColor(Color color);
            Color &getDrawColor() const;
            Color &setClearColor(Color color);
            Color &getClearColor() const;
            void setFont(Font *font);
            void drawSurface(SDL_Surface *surface, Sint32 x, Sint32 y);
            void drawTexture(SDL_Texture *texture, Sint32 x, Sint32 y);
            void drawText(std::string text, Sint32 x, Sint32 y);
            void drawRect(MATH::Rect rect);
            void drawObject(GUI::Object *object);
            void drawLayout(GUI::LayoutContainer *container);
        };
    }
}

#endif //TURBO_RENDERER_H
