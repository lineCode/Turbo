#include "video/renderer.h"

namespace TURBO
{
    namespace VIDEO
    {
        Renderer::Renderer(Window &window, int index, Uint32 flags)
            : window(window),
              text_mode(TEXT_MODE::BLENDED),
              color_text_fg(255, 255, 255, 255),
              color_text_bg(0, 0, 0, 255),
              color_draw(255, 255, 255, 255),
              color_clear(0, 0, 0, 255)
        {
            renderer = SDL_CreateRenderer(window.getWindow(), index, flags);
            font = new Font(TURBO_DEFAULT_FONT, TURBO_DEFAULT_FONT_SIZE, 0);
            font_collection = new FontCollection(TURBO_DEFAULT_FONT, 10, 50, 10);
            font_texture = new Texture(this->getRenderer(), window.getSize().w, window.getSize().h);
        }

        Renderer::~Renderer()
        {
            delete font_texture;
            delete font_collection;
            delete font;
            SDL_DestroyRenderer(renderer);
        }

        SDL_Renderer * Renderer::getRenderer()
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
                SDL_RenderCopyEx(renderer, texture->getTexture(), nullptr, &dest, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
            }
        }

        void Renderer::drawTexture(Texture *texture, MATH::Rect dest)
        {
            if(texture != nullptr)
            {
                SDL_Rect dest_rect = {dest.x, dest.y,
                                      std::min(texture->getWidth(), dest.w),
                                      std::min(texture->getHeight(), dest.h)};
                SDL_RenderCopyEx(renderer, texture->getTexture(), nullptr, &dest_rect, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
            }
        }

        Texture *Renderer::createUTF8Text(std::string &text, Sint32 w, Sint32 h)
        {
            SDL_Surface *surface = nullptr;
            Texture *texture = nullptr;

            // TODO choose optimal font size

            if(text_mode == VIDEO::TEXT_MODE::SOLID)
            {
                surface = TTF_RenderUTF8_Solid(font->getFont(), text.c_str(), color_text_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::BLENDED)
            {
                surface = TTF_RenderUTF8_Blended(font->getFont(), text.c_str(), color_text_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::SHADED)
            {
                surface = TTF_RenderUTF8_Shaded(font->getFont(), text.c_str(), color_text_fg.toSDLColor(), color_text_bg.toSDLColor());
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
            Texture * texture = nullptr;

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
                surface = TTF_RenderUNICODE_Shaded(font->getFont(), text, color_text_fg.toSDLColor(), color_text_bg.toSDLColor());
            }

            if(surface != nullptr)
            {
                texture = new Texture(renderer, surface);
                SDL_FreeSurface(surface);
            }
            return texture;
        }

        void Renderer::drawRect(MATH::Rect rect, Color color, bool filled)
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

        void Renderer::drawPolygon(std::vector<MATH::Point> points, bool filled)
        {
            if(filled)
            {
                //filledPolygonColor(renderer, nullptr, nullptr, 0, color_draw.toHexColor());
            }
            else
            {
                //polygonColor(renderer, );
            }
        }
    }
}