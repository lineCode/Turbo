#ifndef TURBO_RENDERER_H
#define TURBO_RENDERER_H

#include <iostream>
#include <vector>

#include <SDL_video.h>
#include <SDL_types.h>
#include <SDL2_gfxPrimitives.h>

#include "video/video_def.h"
#include "system/sdl.h"
#include "util/log.h"
#include "video/color.h"
#include "video/font.h"
#include "video/texture.h"
#include "video/window.h"

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
            FontCollection *font_collection;
            Texture        *font_texture;
            TEXT_MODE      text_mode;
            Color          color_text_fg;
            Color          color_text_bg;
            Color          color_draw;
            Color          color_clear;

        public:
            Renderer(Window &window, int index, Uint32 flags);

            ~Renderer();

            SDL_Renderer *getRenderer();

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

            Font *getFont();

            Font *setFont(Font *font);

            FontCollection *getFontCollection();

            FontCollection *setFontCollection(FontCollection *font_collection);

            TEXT_MODE setTextMode(TEXT_MODE mode);

            TEXT_MODE getTextMode() const;

            void drawSDLSurface(SDL_Surface *surface, Sint32 x, Sint32 y);

            void drawSDLTexture(SDL_Texture *texture, Sint32 x, Sint32 y);

            void drawTexture(Texture *texture, Sint32 x, Sint32 y);

            void drawTexture(Texture *texture, MATH::Rect dest);

            Texture *createUTF8Text(std::string &text, Sint32 w, Sint32 h, TEXT_ALIGNMENT alignment = TEXT_ALIGNMENT::TOP_LEFT);

            Texture *createUTF8Text(std::string &text, Uint8 pt_size, Sint32 w, Sint32 h);

            Texture *createUnicodeText(const Uint16 *text, Sint32 w, Sint32 h);

            void drawRect(MATH::Rect rect, Color color = Color(255, 255, 255, 255), bool filled = false);

            void drawPolygon(std::vector<MATH::Point> points, bool filled = false);
        };
    }
}

#endif //TURBO_RENDERER_H
