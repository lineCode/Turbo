#include "video/renderer.h"

namespace TURBO
{
    namespace VIDEO
    {
        Renderer::Renderer(Window &window, int index, Uint32 flags)
            : window(window)
        {
            if(SYSTEM::SDL::SDL_IS_INIT)
            {
                renderer        = SDL_CreateRenderer(window.getWindow(), index, flags);
                font            = new Font(TURBO_DEFAULT_FONT_NORMAL, TURBO_DEFAULT_FONT_SIZE, 0);
                font_texture    = new Texture(this->getRenderer(), window.getSize().w, window.getSize().h);
                font_collection = new FontCollection(TURBO_DEFAULT_FONT_NORMAL, 8,
                                                     std::vector<Uint8>{1, 1, 2, 2, 2, 4, 4, 6, 6, 8, 8});

                setBlendMode(blend_mode);

                if(renderer == nullptr)
                {
                    UTIL::Log::err(SDL_GetError());
                }
            }
            else
            {
                UTIL::Log::err("SDL is not initialized");
            }
        }

        Renderer::~Renderer()
        {
            delete font_texture;
            delete font_collection;
            delete font;

            if(renderer != nullptr)
            {
                SDL_DestroyRenderer(renderer);
            }
        }

        SDL_Renderer *Renderer::getRenderer()
        {
            return renderer;
        }

        void Renderer::clear()
        {
            setDrawColor(color_clear);
            SDL_RenderClear(renderer);
            setDrawColor(color_draw);
        }

        void Renderer::present()
        {
            SDL_RenderPresent(renderer);
        }

        SDL_BlendMode Renderer::setBlendMode(SDL_BlendMode mode)
        {
            blend_mode = mode;
            SDL_SetRenderDrawBlendMode(renderer, blend_mode);
            return blend_mode;
        }

        Color &Renderer::setTextColor(Color color)
        {
            color_text_fg = color;
            return color_text_fg;
        }

        Color &Renderer::getTextColor()
        {
            return color_text_fg;
        }

        Color &Renderer::setTextbackgroundColor(Color color)
        {
            color_text_bg = color;
            return color_text_bg;
        }

        Color &Renderer::getTextbackgroundColor()
        {
            return color_text_bg;
        }

        Color &Renderer::setDrawColor(Color color)
        {
            color_draw = color;
            SDL_SetRenderDrawColor(renderer, color_draw.r, color_draw.g, color_draw.b, color_draw.a);
            return color_draw;
        }

        Color &Renderer::getDrawColor()
        {
            return color_draw;
        }

        Color &Renderer::setClearColor(Color color)
        {
            color_clear = color;
            return color_clear;
        }

        Color &Renderer::getClearColor()
        {
            return color_clear;
        }

        Font *Renderer::getFont()
        {
            return font;
        }

        Font *Renderer::setFont(Font *font)
        {
            if(font != nullptr)
            {
                this->font = font;
            }
            return this->font;
        }

        FontCollection *Renderer::getFontCollection()
        {
            return font_collection;
        }

        FontCollection *Renderer::setFontCollection(FontCollection *font_collection)
        {
            if(font_collection == nullptr)
            {
                this->font_collection = font_collection;
            }
            return this->font_collection;
        }

        TEXT_MODE Renderer::setTextMode(TEXT_MODE mode)
        {
            text_mode = mode;
            return text_mode;
        }

        TEXT_MODE Renderer::getTextMode() const
        {
            return text_mode;
        }

        void Renderer::drawSDLSurface(SDL_Surface *surface, Sint32 x, Sint32 y)
        {
            if(surface != nullptr)
            {

            }
        }

        void Renderer::drawSDLTexture(SDL_Texture *texture, Sint32 x, Sint32 y)
        {
            if(texture != nullptr)
            {
                Sint32 w = 0, h = 0;
                SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
                SDL_Rect dest = {x, y, w, h};
                SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
            }
        }

        void Renderer::drawTexture(Texture *texture, Sint32 x, Sint32 y)
        {
            if(texture != nullptr)
            {
                SDL_Rect dest = {x, y, texture->getWidth(), texture->getHeight()};
                SDL_RenderCopyEx(renderer, texture->getTexture(), nullptr, &dest, 0, nullptr,
                                 SDL_RendererFlip::SDL_FLIP_NONE);
            }
        }

        void Renderer::drawTexture(Texture *texture, MATH::Rect dest)
        {
            if(texture != nullptr)
            {
                SDL_Rect dest_rect = {dest.x, dest.y,
                                      std::min(texture->getWidth(), dest.w),
                                      std::min(texture->getHeight(), dest.h)};
                SDL_RenderCopyEx(renderer, texture->getTexture(), nullptr, &dest_rect, 0, nullptr,
                                 SDL_RendererFlip::SDL_FLIP_NONE);
            }
        }

        Texture *Renderer::createUTF8Text(std::string &text, Sint32 w, Sint32 h, FONT_STYLE style,
                                          TEXT_WRAPPING wrapping)
        {
            return createUTF8Text(text, font->getFontSize(), w, h, style, wrapping);
        }

        Texture *Renderer::createUTF8Text(std::string &text, Uint8 size, Sint32 w, Sint32 h, FONT_STYLE style,
                                          TEXT_WRAPPING wrapping)
        {
            SDL_Surface *surface    = nullptr;
            Texture     *texture    = nullptr;
            Font        *font       = font_collection->getLTEFont(size);
            Sint32      text_width  = font->getUTF8TextSize(text).w;
            Sint32      text_height = font->getUTF8TextSize(text).h;

            if(text_width > w)
            {
                // auto rows              = static_cast<Uint8>((text_width / w) + 1);
                // auto optimal_font_size = static_cast<Uint8>((h / rows) * PX_TO_PT);
                if(wrapping == TEXT_WRAPPING::BREAK && text_mode != TEXT_MODE::BLENDED)
                {

                }

            }

            while(text_height > h && size > 1)
            {
                size -= 1;
                font        = font_collection->getLTEFont(size);
                text_height = font->getUTF8TextSize(text).h;
            }

            font->setFontStyle(style);
            TTF_Font *sdl_font = font->getFont();

            if(text_mode == TEXT_MODE::SOLID)
            {
                surface = TTF_RenderUTF8_Solid(sdl_font, text.c_str(), color_text_fg.toSDLColor());
            }
            else if(text_mode == TEXT_MODE::BLENDED)
            {
                if(wrapping == TEXT_WRAPPING::BREAK)
                {
                    surface = TTF_RenderUTF8_Blended_Wrapped(sdl_font, text.c_str(), color_text_fg.toSDLColor(),
                                                             static_cast<Uint32>(w));
                }
                else
                {
                    surface = TTF_RenderUTF8_Blended(sdl_font, text.c_str(), color_text_fg.toSDLColor());
                }
            }
            else if(text_mode == TEXT_MODE::SHADED)
            {
                surface = TTF_RenderUTF8_Shaded(sdl_font, text.c_str(), color_text_fg.toSDLColor(),
                                                color_text_bg.toSDLColor());
            }

            if(surface != nullptr)
            {
                texture = new Texture(renderer, surface);
                SDL_FreeSurface(surface);
            }
            return texture;
        }

        Texture *Renderer::createUnicodeText(const Uint16 *text, Sint32 w, Sint32 h)
        {
            SDL_Surface *surface = nullptr;
            Texture     *texture = nullptr;

            if(text_mode == VIDEO::TEXT_MODE::SOLID)
            {
                surface = TTF_RenderUNICODE_Solid(font->getFont(), text, color_text_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::BLENDED)
            {
                surface = TTF_RenderUNICODE_Blended(font->getFont(), text, color_text_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::SHADED)
            {
                surface = TTF_RenderUNICODE_Shaded(font->getFont(), text, color_text_fg.toSDLColor(),
                                                   color_text_bg.toSDLColor());
            }

            if(surface != nullptr)
            {
                texture = new Texture(renderer, surface);
                SDL_FreeSurface(surface);
            }
            return texture;
        }

        void Renderer::drawPoint(Sint32 x, Sint32 y, Uint8 size, Color color)
        {
            setDrawColor(color);
            SDL_RenderDrawPoint(renderer, x, y);
            setDrawColor(color_draw);
        }

        void Renderer::drawPoint(MATH::Point p, Uint8 size, Color color)
        {
            setDrawColor(color);
            SDL_RenderDrawPoint(renderer, p.x, p.y);
            setDrawColor(color_draw);
        }

        void Renderer::drawLine(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2, Uint8 size, Color color)
        {
            setDrawColor(color);
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
            setDrawColor(color_draw);
        }

        void Renderer::drawLine(MATH::Point p1, MATH::Point p2, Uint8 size, Color color)
        {
            setDrawColor(color);
            SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
            setDrawColor(color_draw);
        }

        void Renderer::drawLine(MATH::Line l, Uint8 size, Color color)
        {
            setDrawColor(color);
            SDL_RenderDrawLine(renderer, l.x1, l.y1, l.x2, l.y2);
            setDrawColor(color_draw);
        }

        void Renderer::drawRect(Sint32 x, Sint32 y, Sint32 w, Sint32 h, Uint8 size, Color color, bool filled)
        {
            SDL_Rect r{x, y, w, h};
            setDrawColor(color);
            if(filled)
            {
                SDL_RenderFillRect(renderer, &r);
            }
            else
            {
                SDL_RenderDrawRect(renderer, &r);
            }
            setDrawColor(color_draw);
        }

        void Renderer::drawRect(MATH::Rect rect, Uint8 size, Color color, bool filled)
        {
            SDL_Rect r{rect.x, rect.y, rect.w, rect.h};
            setDrawColor(color);
            if(filled)
            {
                SDL_RenderFillRect(renderer, &r);
            }
            else
            {
                SDL_RenderDrawRect(renderer, &r);
            }
            setDrawColor(color_draw);
        }

        void Renderer::drawCircle(MATH::Point p, Sint32 r, Uint8 size, Color color, bool filled)
        {
            if(filled)
            {
                filledCircleColor(renderer, static_cast<Sint16>(p.x), static_cast<Sint16>(p.y), static_cast<Sint16>(r),
                                  color.toHexColor());
            }
            else
            {
                circleColor(renderer, static_cast<Sint16>(p.x), static_cast<Sint16>(p.y), static_cast<Sint16>(r),
                            color.toHexColor());
            }
        }

        void Renderer::drawPolygon(std::vector<MATH::Point> &points, Color color, bool filled)
        {
            Sint16 x[points.size()] = {0};
            Sint16 y[points.size()] = {0};

            for(int i = 0; i < points.size(); ++i)
            {
                x[i] = static_cast<Sint16>(points[i].x);
                y[i] = static_cast<Sint16>(points[i].y);
            }

            if(filled)
            {
                filledPolygonColor(renderer, x, y, static_cast<int>(points.size()), color.toHexColor());
            }
            if(filled)
            {
                polygonColor(renderer, x, y, static_cast<int>(points.size()), color.toHexColor());
            }
        }
    }
}