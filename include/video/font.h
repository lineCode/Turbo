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
        /**
         * Rough transformation ratios.
         */
        const float PX_TO_PT = 4 / 3; // 1.3
        const float PT_TO_PX = 3 / 4; // 0.75

        /**
         * Font style defines the appearance of letters.
         */
        enum class FONT_STYLE
            : Uint8
        {
            NORMAL     = TTF_STYLE_NORMAL,
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

        /**
         * Describes the encoding type of the letter.
         */
        enum class FONT_TYPE
            : Uint8
        {
            GLYPH   = 0x0,
            UTF8    = 0x1,
            UNICODE = 0x2
        };

        /**
         * Size information of a font.
         */
        struct FontMetrics
        {
            Uint16 c;
            Sint32 min_x;
            Sint32 max_x;
            Sint32 min_y;
            Sint32 max_y;
            Sint32 advance;
        };

        /**
         * Rendering method for texts.
         */
        enum class TEXT_MODE
            : Uint8
        {
            SOLID   = 0x0,
            BLENDED = 0x1,
            SHADED  = 0x2
        };

        /**
         *
         */
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

        /**
         * This class hold multiple fonts with different sizes in it, to give the renderer more options.
         */
        class FontCollection
        {
        private:
            std::map<Uint8, Font *> fonts;

        public:
            /**
             * Takes a path to the font, a starting size, an ending size and a step number.
             * Creates a set of fonts in different sizes from the given range.
             * @param path
             * @param from
             * @param to
             * @param step
             */
            explicit FontCollection(std::string path, Uint8 from = 1, Uint8 to = 10, Uint8 step = 1);
            explicit FontCollection(std::string path, Uint8 from = 1, std::vector<Uint8> step = {1});

            /**
             * Takes a path to the font and a vector of the sizes that should be created.
             * Creates a set of fonts in different sizes.
             * @param path
             * @param sizes
             */
            FontCollection(std::string path, std::vector<Uint8> sizes);

            /**
             * Cleans up allocated fonts.
             */
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
