#include "video/font.h"

namespace TURBO
{
    namespace VIDEO
    {
        Font::Font(const std::string filepath, Uint8 ptsize, Uint8 index)
        {
            font = TTF_OpenFontIndex(path.c_str(), ptsize, index);

            if(font != nullptr)
            {
                path = filepath;
                pt_size = ptsize;
                loadFontInfo();
            }
        }

        Font::~Font()
        {
            TTF_CloseFont(font);
        }

        void Font::loadFontInfo()
        {
            font_family = TTF_FontFaceFamilyName(font);
            font_style = TTF_FontFaceStyleName(font);
            height = static_cast<Uint32>(TTF_FontHeight(font));
            ascent = static_cast<Uint32>(TTF_FontAscent(font));
            descent = TTF_FontDescent(font);
            lineskip = static_cast<Uint32>(TTF_FontLineSkip(font));
            faces = static_cast<Uint64>(TTF_FontFaces(font));
            fixed = (TTF_FontFaceIsFixedWidth(font) > 0);
            style = static_cast<FONT_STYLE>(TTF_GetFontStyle(font));
            hinting = static_cast<FONT_HINTING>(TTF_GetFontHinting(font));
            outline = static_cast<Uint32>(TTF_GetFontOutline(font));
            kerning = static_cast<Uint32>(TTF_GetFontKerning(font));
        }

        TTF_Font * Font::getFont()
        {
            return font;
        }

        Uint32 Font::getFontHeight()
        {
            return height;
        }

        Uint32 Font::getFontAscent()
        {
            return ascent;
        }

        Sint32 Font::getFontDescent()
        {
            return descent;
        }

        Uint32 Font::getFontLineSkip()
        {
            return lineskip;
        }

        Uint64 Font::getFontFaces()
        {
            return faces;
        }

        bool Font::isFixedWith()
        {
            return fixed;
        }

        std::string Font::getFontFamilyName()
        {
            return font_family;
        }

        std::string Font::getFontStyleName()
        {
            return font_style;
        }

        FONT_STYLE Font::getFontStyle()
        {
            return style;
        }

        FONT_STYLE Font::setFontSTyle(FONT_STYLE style)
        {
            if(font != nullptr)
            {
                TTF_SetFontStyle(font, static_cast<int>(style));
                this->style = style;
            }
            return style;
        }

        Uint32 Font::getFontOutline()
        {
            return outline;
        }

        Uint32 Font::setFontOutline(Sint32 outline)
        {
            if(font != nullptr)
            {
                TTF_SetFontOutline(font, outline);
                this->outline = static_cast<Uint32>(outline);
            }
            return this->outline;
        }

        FONT_HINTING Font::getFontHinting()
        {
            return hinting;
        }

        FONT_HINTING Font::setFontHinting(FONT_HINTING hinting)
        {
            if(font != nullptr)
            {
                TTF_SetFontHinting(font, static_cast<int>(hinting));
                this->hinting = hinting;
            }
            return this->hinting;
        }

        Uint32 Font::getFontKerning()
        {
            return kerning;
        }

        Uint32 Font::setFontKerning(Sint32 kerning)
        {
            if(font != nullptr)
            {
                TTF_SetFontKerning(font, kerning);
                this->kerning = static_cast<Uint32>(kerning);
            }
            return this->kerning;
        }

        bool Font::hasGlyph(Uint16 c)
        {
            if(font != nullptr)
            {
                return (TTF_GlyphIsProvided(font, c) > 0);
            }
            return false;
        }

        FontMetrics Font::getMetrics(Uint16 c)
        {
            FontMetrics m = {};
            if(font != nullptr)
            {
                m.c = c;
                TTF_GlyphMetrics(font, m.c, &m.min_x, &m.max_x, &m.min_y, &m.max_y, &m.advance);
            }
            return m;
        }

        MATH::Vector Font::getUTF8TextSize(std::string text)
        {
            int w = 0, h = 0;

            if(font != nullptr)
            {
                TTF_SizeText(font, text.c_str(), &w, &h);
            }

            return MATH::Vector{w, h, 0};
        }

        MATH::Vector Font::getUnicodeTextSize(const Uint16 *text)
        {
            int w = 0, h = 0;

            if(font != nullptr)
            {
                TTF_SizeUNICODE(font, text, &w, &h);
            }
            return MATH::Vector{w, h, 0};
        }
    }
}