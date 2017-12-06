#include "video/renderer.h"

namespace TURBO
{
    namespace VIDEO
    {
        Renderer::Renderer(Window & window, int index, Uint32 flags)
            : SDL2pp::Renderer(window, index, flags),
              window(window),
              color_fg(255.f, 255.f, 255.f, 255.f),
              color_bg(255.f, 255.f, 255.f, 255.f),
              color_clear(255.f, 255.f, 255.f, 255.f)
        {

        }

        void Renderer::clear()
        {
            OpenGL::clear();
        }

        void Renderer::present()
        {
            OpenGL::swap(window);
        }

        void Renderer::setFont(Font * font)
        {
            this->font = font;
        }

        void Renderer::draw()
        {

        }

        void Renderer::drawText(std::string text)
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
                surface = TTF_RenderText_Shaded(font->Get(), text.c_str(), color_fg.toSDLColor(),
                                                color_bg.toSDLColor());
            }

            if(surface != nullptr)
            {
                GLenum data_format = GL_RGBA;
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, data_format, GL_UNSIGNED_BYTE, surface->pixels);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                SDL_FreeSurface(surface);
            }
        }

        void Renderer::drawRect(MATH::Rect rect)
        {

        }
    }
}