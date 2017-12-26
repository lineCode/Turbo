#include "video/renderer.h"

namespace TURBO
{
    namespace VIDEO
    {
        Renderer::Renderer(Window &window, int index, Uint32 flags)
            : window(window),
              text_mode(TEXT_MODE::BLENDED),
              color_text_fg(255, 255, 0, 255),
              color_text_bg(255, 255, 255, 255),
              color_draw(255, 255, 255, 255),
              color_clear(0, 0, 0, 255)
        {
            renderer = SDL_CreateRenderer(window.getWindow(), index, flags);
            font = new Font(TURBO_DEFAULT_FONT, TURBO_DEFAULT_FONT_SIZE, 0);
        }

        Renderer::~Renderer()
        {
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

        Font *Renderer::setFont(Font *font)
        {
            if(font != nullptr)
            {
                this->font = font;
            }
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

        void Renderer::drawSurface(SDL_Surface *surface, Sint32 x, Sint32 y)
        {
            if(surface != nullptr)
            {

            }
        }

        void Renderer::drawTexture(SDL_Texture *texture, Sint32 x, Sint32 y)
        {
            if(texture != nullptr)
            {

            }
        }

        void Renderer::drawText(std::string text, Sint32 x, Sint32 y)
        {
            SDL_Surface *surface = nullptr;
            if(text_mode == VIDEO::TEXT_MODE::SOLID)
            {
                surface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color_text_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::BLENDED)
            {
                surface = TTF_RenderText_Blended(font->getFont(), text.c_str(), color_text_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::SHADED)
            {
                surface = TTF_RenderText_Shaded(font->getFont(), text.c_str(), color_text_fg.toSDLColor(), color_text_bg.toSDLColor());
            }

            if(surface != nullptr)
            {
                //drawSurface(surface, x, y);
                SDL_Rect s = {0, 0, surface->w, surface->h};
                SDL_Rect d = {x, y, surface->w, surface->h};
                SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_RenderCopy(renderer, tex, &s, &d);
                SDL_DestroyTexture(tex);
                SDL_FreeSurface(surface);
            }
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
                //filledPolygonColor(renderer, );
            }
            else
            {
                //polygonColor(renderer, );
            }
        }

        void Renderer::drawObject(GUI::Object *object)
        {
            if(object != nullptr)
            {
                if(object->getObjectType() >= GUI::OBJECT_TYPE::WIDGET)
                {
                    if(object->getSize() <= window.getSize())
                    {
                        GUI::Color c = object->getBackground().background_color;
                        drawRect(object->getSize(), Color(c.r, c.g, c.b, c.a), true);
                        if(object->getObjectType() == GUI::OBJECT_TYPE::BUTTON)
                        {
                            auto button = dynamic_cast<GUI::Button*>(object);
                            setTextColor(Color(0, 255, 0, 255));
                            drawText(button->getText(), button->getSize().x, button->getSize().y);
                        }

                        if(object->getChild() != nullptr)
                        {
                            drawObject(object->getChild());
                        }
                    }
                }
                else if(object->getObjectType() >= GUI::OBJECT_TYPE::LAYOUT)
                {
                    auto container = dynamic_cast<GUI::LayoutContainer*>(object);
                    drawLayout(container);
                }
            }
        }

        void Renderer::drawLayout(GUI::LayoutContainer *container)
        {
            if(container != nullptr)
            {
                if(container->getObjectType() == GUI::OBJECT_TYPE::LAYOUT)
                {
                    for(auto & child : container->getChildren())
                    {
                        drawObject(child);
                    }
                }
            }
        }
    }
}