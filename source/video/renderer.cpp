#include "video/renderer.h"

namespace TURBO
{
    namespace VIDEO
    {
        Renderer::Renderer(Window &window, int index, Uint32 flags)
            : window(window),
              text_mode(TEXT_MODE::BLENDED),
              color_fg(255, 255, 0, 255),
              color_bg(255, 255, 255, 255),
              color_text(255, 255, 255, 255),
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

        void Renderer::setFont(Font *font)
        {
            if(font != nullptr)
            {
                this->font = font;
            }
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
                surface = TTF_RenderText_Solid(font->Get(), text.c_str(), color_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::BLENDED)
            {
                surface = TTF_RenderText_Blended(font->Get(), text.c_str(), color_fg.toSDLColor());
            }
            else if(text_mode == VIDEO::TEXT_MODE::SHADED)
            {
                surface = TTF_RenderText_Shaded(font->Get(), text.c_str(), color_fg.toSDLColor(), color_bg.toSDLColor());
            }

            drawSurface(surface, x, y);

            if(surface != nullptr)
            {
                SDL_FreeSurface(surface);
            }
        }

        void Renderer::drawRect(MATH::Rect rect)
        {
            SDL_Rect r{rect.x, rect.y, rect.w, rect.h};
            //SDL_RenderDrawRect(renderer, &r);
            SDL_RenderFillRect(renderer, &r);
        }

        void Renderer::drawObject(GUI::Object *object)
        {
            if(object != nullptr)
            {
                if(object->getType() >= GUI::OBJECT_TYPE::WIDGET)
                {
                    if(object->getSize() <= window.getSize())
                    {
                        GUI::Color color = object->getBackground().background_color;
                        drawRect(object->getSize());
                        if(object->getChild() != nullptr)
                        {
                            drawObject(object->getChild());
                        }
                    }
                }
                else if(object->getType() >= GUI::OBJECT_TYPE::LAYOUT)
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
                if(container->getType() == GUI::OBJECT_TYPE::LAYOUT)
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