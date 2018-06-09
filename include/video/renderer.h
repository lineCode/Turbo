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
        /**
         * Alignment of texts.
         */
        enum class TEXT_ALIGNMENT
            : Uint8
        {
            LEFT          = 0x01,
            CENTER        = 0x02,
            RIGHT         = 0x04,
            TOP           = 0x10,
            MIDDLE        = 0x20,
            BOTTOM        = 0x40,
            TOP_LEFT      = 0x11,
            TOP_CENTER    = 0x12,
            TOP_RIGHT     = 0x14,
            MIDDLE_LEFT   = 0x21,
            MIDDLE_CENTER = 0x22,
            MIDDLE_RIGHT  = 0x24,
            BOTTOM_LEFT   = 0x41,
            BOTTOM_CENTER = 0x42,
            BOTTOM_RIGHT  = 0x44
        };

        Uint8 operator&(TEXT_ALIGNMENT l, Uint8 r);

        /**
         * Wrapping behaviour of texts.
         */
        enum class TEXT_WRAPPING
            : Uint8
        {
            OVERFLOW_RIGHT = 0x01,
            OVERFLOW_LEFT  = 0x02,
            CUT_RIGHT      = 0x04,
            CUT_LEFT       = 0x08,
            BREAK          = 0x0F
        };

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
            Color          color_text_fg = Color{255, 255, 255, 255};
            Color          color_text_bg = Color{0, 0, 0, 255};
            Color          color_draw    = Color{255, 255, 255, 255};
            Color          color_clear   = Color{0, 0, 0, 255};

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

            Texture * createUTF8Text(std::string &text, Sint32 w, Sint32 h, Uint8 size,
                                     TEXT_ALIGNMENT alignment = TEXT_ALIGNMENT::TOP_LEFT,
                                     TEXT_WRAPPING wrapping = TEXT_WRAPPING::BREAK);

            Texture *createUTF8Text(std::string &text, Uint8 pt_size, Sint32 w, Sint32 h);

            Texture *createUnicodeText(const Uint16 *text, Sint32 w, Sint32 h);

            void drawPoint(Sint32 x, Sint32 y, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

            void drawPoint(MATH::Point p, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

            void drawLine(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2, Uint8 size = 1,
                          Color color = Color(255, 255, 255, 255));

            void drawLine(MATH::Point p1, MATH::Point p2, Uint8 size = 1, Color color = Color(255, 255, 255, 255));

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
