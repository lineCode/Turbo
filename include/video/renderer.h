#ifndef TURBO_RENDERER_H
#define TURBO_RENDERER_H

#include <iostream>

#include <SDL_video.h>
#include <SDL_types.h>
#include <SDL2_gfxPrimitives.h>

#include "video/video_def.h"
#include "video/window.h"
#include "video/color.h"
#include "video/font.h"
#include "gui/object.h"
#include "gui/layout.h"
#include "gui/button.h"

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
            Color           color_text_fg;
            Color           color_text_bg;
            Color           color_draw;
            Color           color_clear;

        public:
            Renderer(Window & window, int index, Uint32 flags);
            ~Renderer();
            SDL_Renderer * getRenderer();
            void clear();
            void present();
            Color &setTextColor(Color color);
            Color &getTextColor();
            Color &setTextbackgroundColor(Color color);
            Color &getTextbackgroundColor();
            Color &setDrawColor(Color color);
            Color &getDrawColor();
            Color &setClearColor(Color color);
            Color &getClearColor();
            Font *setFont(Font *font);
            TEXT_MODE setTextMode(TEXT_MODE mode);
            TEXT_MODE getTextMode() const;
            void drawSurface(SDL_Surface *surface, Sint32 x, Sint32 y);
            void drawTexture(SDL_Texture *texture, Sint32 x, Sint32 y);
            void drawText(std::string text, Sint32 x, Sint32 y);
            void drawRect(MATH::Rect rect, Color color = Color(255, 255, 255, 255), bool filled = false);
            void drawPolygon(std::vector<MATH::Point> points, bool filled = false);
            void drawObject(GUI::Object *object);
            void drawLayout(GUI::LayoutContainer *container);
        };
    }
}

#endif //TURBO_RENDERER_H
