#ifndef TURBO_FONT_H
#define TURBO_FONT_H

#include <map>
#include <algorithm>

#include <SDL_ttf.h>

#include "video/video_def.h"
#include "util/log.h"
#include "math/rect.h"
#include "system/sdl.h"

namespace TURBO
{
    namespace VIDEO
    {
        const float PX_TO_PT = 8 / 6; // 1.3
        const float PT_TO_PX = 6 / 8; // 0.75

        enum class FONT_STYLE
            : Uint8
        {
            BOLD       = TTF_STYLE_BOLD,
            ITALIC     = TTF_STYLE_ITALIC,
            UNDERLINED = TTF_STYLE_UNDERLINE,
            STRIKED    = TTF_STYLE_STRIKETHROUGH
        };


        /**
         * Hinting is responsible for edge smoothing and contrast
         */
        enum class FONT_HINTING
            : Uint8
        {
            NORMAL = TTF_HINTING_NORMAL,
            LIGHT  = TTF_HINTING_LIGHT,
            MONO   = TTF_HINTING_MONO,
            NONE   = TTF_HINTING_NONE
        };


        enum class FONT_TYPE
            : Uint8
        {
            GLYPH = 0x0,
            UTF8 = 0x1,
            UNICODE = 0x2
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


        enum class TEXT_MODE
            : Uint8
        {
            SOLID   = 0x0,
            BLENDED = 0x1,
            SHADED  = 0x2
        };


        enum class TEXT_ALIGNMENT
            : Uint8
        {
            LEFT          = 0x01,
            CENTER        = 0x02,
            RIGHT         = 0x03,
            TOP           = 0x10,
            MIDDLE        = 0x20,
            BOTTOM        = 0x30,
            TOP_LEFT      = 0x11,
            TOP_CENTER    = 0x12,
            TOP_RIGHT     = 0x13,
            MIDDLE_LEFT   = 0x21,
            MIDDLE_CENTER = 0x22,
            MIDDLE_RIGHT  = 0x23,
            BOTTOM_LEFT   = 0x31,
            BOTTOM_CENTER = 0x32,
            BOTTOM_RIGHT  = 0x33
        };


        class Font
        {
        private:
            TTF_Font     *font;
            std::string  path;
            std::string  font_family;
            std::string  font_style;
            Uint8        pt_size;
            Uint32       height;
            Uint32       ascent;
            Sint32       descent;
            Uint32       lineskip;
            Uint64       faces;
            bool         fixed;
            FONT_STYLE   style;
            FONT_HINTING hinting;
            Uint32       outline;
            Uint32       kerning;

        public:
            Font(std::string path, Uint8 ptsize, Uint8 index = 0);

            ~Font();

            TTF_Font *getFont();

            void loadFontInfo();

            Uint8 setFontSize(Uint8 size);

            Uint8 getFontSize();

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

            MATH::Rect getUTF8TextSize(std::string text);

            MATH::Rect getUnicodeTextSize(const Uint16 *text);
        };


        class FontCollection
        {
        private:
            std::map<Uint8, Font *> fonts;

        public:
            explicit FontCollection(std::string path, Uint8 from = 1, Uint8 to = 10, Uint8 step = 1);

            FontCollection(std::string path, std::vector<Uint8> sizes);

            ~FontCollection();

            /**
             * Searches for a font that has the requested  size
             * @param size the requested size
             * @return A pointer to a font saved in the fonts, or nullptr if non available
             */
            Font *getFont(Uint8 size);

            /**
             * Searches for a font that has the requested or a smaller size
             * @param size the requested size
             * @return A pointer to a font saved in the fonts, or nullptr if non available
             */
            Font *getLTEFont(Uint8 size);

            /**
             * Searches for a font that has the requested or a greater size
             * @param size the requested size
             * @return A pointer to a font saved in the fonts, or nullptr if non available
             */
            Font *getGTEFont(Uint8 size);
        };
    }
}

#endif //TURBO_FONT_H
