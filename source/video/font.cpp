#include "video/font.h"

namespace TURBO
{
    namespace VIDEO
    {
        Font::Font(const std::string filepath, Uint8 ptsize, Uint8 index)
            : path(filepath), pt_size(ptsize)
        {
            if(SYSTEM::SDL::TTF_IS_INIT)
            {
                font = TTF_OpenFontIndex(filepath.c_str(), ptsize, index);

                if(font != nullptr)
                {
                    loadFontInfo();
                }
                else
                {
                    UTIL::Log::err(TTF_GetError());
                }
            }
            else
            {
                UTIL::Log::err("SDL TTF is not initialized");
            }
        }

        Font::~Font()
        {
            if(font != nullptr)
            {
                TTF_CloseFont(font);
            }
        }

        void Font::loadFontInfo()
        {
            font_family = TTF_FontFaceFamilyName(font);
            font_style  = TTF_FontFaceStyleName(font);
            height      = static_cast<Uint32>(TTF_FontHeight(font));
            ascent      = static_cast<Uint32>(TTF_FontAscent(font));
            descent     = TTF_FontDescent(font);
            lineskip    = static_cast<Uint32>(TTF_FontLineSkip(font));
            faces       = static_cast<Uint64>(TTF_FontFaces(font));
            fixed       = (TTF_FontFaceIsFixedWidth(font) > 0);
            style       = static_cast<FONT_STYLE>(TTF_GetFontStyle(font));
            hinting     = static_cast<FONT_HINTING>(TTF_GetFontHinting(font));
            outline     = static_cast<Uint32>(TTF_GetFontOutline(font));
            kerning     = static_cast<Uint32>(TTF_GetFontKerning(font));
        }

        TTF_Font *Font::getFont()
        {
            return font;
        }

        Uint8 Font::setFontSize(Uint8 size)
        {
            if(font != nullptr)
            {
                TTF_CloseFont(font);
            }
            font    = TTF_OpenFont(path.c_str(), size);
            pt_size = size;
            return pt_size;
        }

        Uint8 Font::getFontSize()
        {
            return pt_size;
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

        VIDEO::FONT_STYLE Font::getFontStyle()
        {
            return style;
        }

        VIDEO::FONT_STYLE Font::setFontStyle(VIDEO::FONT_STYLE style)
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

        VIDEO::FONT_HINTING Font::getFontHinting()
        {
            return hinting;
        }

        VIDEO::FONT_HINTING Font::setFontHinting(VIDEO::FONT_HINTING hinting)
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

        MATH::Rect Font::getUTF8TextSize(std::string text)
        {
            int w = 0, h = 0;

            if(font != nullptr)
            {
                TTF_SizeText(font, text.c_str(), &w, &h);
            }
            return {0, 0, w, h};
        }

        MATH::Rect Font::getUnicodeTextSize(const Uint16 *text)
        {
            int w = 0, h = 0;

            if(font != nullptr)
            {
                TTF_SizeUNICODE(font, text, &w, &h);
            }
            return {0, 0, w, h};
        }

        FontCollection::FontCollection(std::string path, Uint8 from, Uint8 to, Uint8 step)
        {
            Uint8 min = 1;

            for(Uint8 i = std::max(from, min); i <= std::max(to, min); i += std::max(step, min))
            {
                if(fonts.count(i) == 0 && i > 0)
                {
                    Font *font = new Font(path, i);
                    fonts[i] = font;
                }
            }
        }

        FontCollection::FontCollection(std::string path, Uint8 from, std::vector<Uint8> step)
        {
            Uint8 min = 1;
            from = std::max(from, min);

            if(fonts.count(from) == 0)
            {
                Font *font = new Font(path, from);
                fonts[from] = font;
            }

            for(const auto &s : step)
            {
                from += s;
                if(fonts.count(from) == 0)
                {
                    Font *font = new Font(path, from);
                    fonts[from] = font;
                }
            }
        }

        FontCollection::FontCollection(std::string path, std::vector<Uint8> sizes)
        {
            for(const auto &size : sizes)
            {
                if(fonts.count(size) == 0 && size > 0)
                {
                    Font *font = new Font(path, size);
                    fonts[size] = font;
                }
            }
        }

        FontCollection::~FontCollection()
        {
            for(const auto &font : fonts)
            {
                delete font.second;
            }
        }

        Font *FontCollection::getFont(Uint8 size)
        {
            if(fonts.count(size) > 0)
            {
                return fonts[size];
            }
            return fonts.begin()->second;
        }

        Font *FontCollection::getLTEFont(Uint8 size)
        {
            if(fonts.count(size) > 0)
            {
                return fonts[size];
            }
            else
            {
                for(auto i = fonts.begin(); i != fonts.end(); ++i)
                {
                    if(i->first > size)
                    {
                        return (--i)->second;
                    }
                }
                return fonts.end()->second;
            }
        }

        Font *FontCollection::getGTEFont(Uint8 size)
        {
            if(fonts.count(size) > 0)
            {
                return fonts[size];
            }
            else
            {
                for(auto i = fonts.begin(); i != fonts.end(); ++i)
                {
                    if(i->first > size)
                    {
                        return i->second;
                    }
                }
                return fonts.end()->second;
            }
        }
    }
}