#ifndef TURBO_FONT_H
#define TURBO_FONT_H

#include <SDL_ttf.h>

#include "video/video_def.h"
#include "math/vector.h"

namespace TURBO
{
    namespace VIDEO
    {
        enum class FONT_STYLE : Uint8
        {
            BOLD = TTF_STYLE_BOLD,
            ITALIC = TTF_STYLE_ITALIC,
            UNDERLINED = TTF_STYLE_UNDERLINE,
            STRIKED = TTF_STYLE_STRIKETHROUGH
        };

        /**
         * Hinting is responsible for edge smoothing and contrast
         */
        enum class FONT_HINTING : Uint8
        {
            NORMAL = TTF_HINTING_NORMAL,
            LIGHT = TTF_HINTING_LIGHT,
            MONO = TTF_HINTING_MONO,
            NONE = TTF_HINTING_NONE
        };

        struct FontMetrics
        {
            Uint16 c;
            Sint32 min_x;
            Sint32 max_x;
            Sint32 min_y;
            Sint32 max_y;
            Sint32 advance;
        };

        class Font
        {
        private:
            TTF_Font * font;
            std::string path;
            std::string font_family;
            std::string font_style;
            Uint8 pt_size;
            Uint32 height;
            Uint32 ascent;
            Sint32 descent;
            Uint32 lineskip;
            Uint64 faces;
            bool fixed;
            FONT_STYLE style;
            FONT_HINTING hinting;
            Uint32 outline;
            Uint32 kerning;

        public:
            Font(std::string path, Uint8 ptsize, Uint8 index = 0);
            ~Font();
            TTF_Font * getFont();
            void loadFontInfo();
            Uint32 getFontHeight();
            Uint32 getFontAscent();
            Sint32 getFontDescent();
            Uint32 getFontLineSkip();
            Uint64 getFontFaces();
            bool isFixedWith();
            std::string getFontFamilyName();
            std::string getFontStyleName();
            FONT_STYLE getFontStyle();
            FONT_STYLE setFontSTyle(FONT_STYLE style);
            Uint32 getFontOutline();
            Uint32 setFontOutline(Sint32 outline);
            FONT_HINTING getFontHinting();
            FONT_HINTING setFontHinting(FONT_HINTING hinting);
            Uint32 getFontKerning();
            Uint32 setFontKerning(Sint32 kerning);
            bool hasGlyph(Uint16 c);
            FontMetrics getMetrics(Uint16 c);
            MATH::Vector getUTF8TextSize(std::string text);
            MATH::Vector getUnicodeTextSize(const Uint16 * text);
        };
    }
}

#endif //TURBO_FONT_H