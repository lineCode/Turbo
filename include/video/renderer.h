#ifndef TURBO_RENDERER_H
#define TURBO_RENDERER_H

#include <iostream>
#include <vector>

#include <SDL_video.h>
#include <SDL_image.h>
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
            SDL_BlendMode  blend_mode    = SDL_BlendMode::SDL_BLENDMODE_BLEND;
            TEXT_MODE      text_mode     = TEXT_MODE::BLENDED;
            Color          color_text_fg = WHITE;
            Color          color_text_bg = BLACK;
            Color          color_draw    = WHITE;
            Color          color_clear   = BLACK;

        public:
            Renderer(Window &window, int index, Uint32 flags);

            ~Renderer();

            SDL_Renderer *getRenderer();

            void clear();

            void present();

            SDL_BlendMode setBlendMode(SDL_BlendMode mode);

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

            Texture *createUTF8Text(std::string &text, Sint32 w, Sint32 h,
                                    FONT_STYLE style = FONT_STYLE::NORMAL,
                                    TEXT_WRAPPING wrapping = TEXT_WRAPPING::BREAK);

            Texture *createUTF8Text(std::string &text, Uint8 size, Sint32 w, Sint32 h,
                                    FONT_STYLE style = FONT_STYLE::NORMAL,
                                    TEXT_WRAPPING wrapping = TEXT_WRAPPING::BREAK);

            Texture *createUnicodeText(const Uint16 *text, Sint32 w, Sint32 h);

            void drawPoint(Sint32 x, Sint32 y, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

            void drawPoint(MATH::Point p, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

            void drawLine(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2, Uint8 size = 1,
                          Color color = Color(255, 255, 255, 255));

            void drawLine(MATH::Point p1, MATH::Point p2, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

            void drawLine(MATH::Line l, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

            void
            drawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint8 size = 1, Color color = Color(255, 255, 255, 255),
                     bool filled = false);

            void
            drawRect(MATH::Rect rect, Uint8 size = 1, Color color = Color(255, 255, 255, 255), bool filled = false);

            void drawCircle(MATH::Point p, Sint32 r, Uint8 size = 1, Color color = Color(255, 255, 255, 255),
                            bool filled = false);

            void
            drawPolygon(std::vector<MATH::Point> &points, Color color = Color(255, 255, 255, 255), bool filled = false);
        };
    }
}

#endif //TURBO_RENDERER_H