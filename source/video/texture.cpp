#include "video/texture.h"

namespace TURBO
{
    namespace VIDEO
    {
        Texture::Texture(SDL_Renderer *renderer, Sint32 w, Sint32 h, Uint32 format, Sint32 access)
            : renderer(renderer), w(w), h(h), format(format), access(access)
        {
            if(SYSTEM::SDL::SDL_IS_INIT)
            {
                texture = SDL_CreateTexture(renderer, format, access, w, h);
                if(texture != nullptr)
                {
                    loadTextureInfo();
                }
                else
                {
                    UTIL::Log::err(SDL_GetError());
                }
            }
            else
            {
                UTIL::Log::err("SDL is not initialized");
            }
        }

        Texture::Texture(SDL_Renderer *renderer, SDL_Surface *surface)
            : renderer(renderer)
        {
            if(SYSTEM::SDL::SDL_IS_INIT)
            {
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                if(texture != nullptr)
                {
                    loadTextureInfo();
                }
                else
                {
                    UTIL::Log::err(SDL_GetError());
                }
            }
            else
            {
                UTIL::Log::err("SDL is not initialized");
            }
        }

        void Texture::loadTextureInfo()
        {
            Sint32 w = 0, h = 0, acc = 0;
            Uint32 form = 0;

            if(texture != nullptr)
            {
                SDL_QueryTexture(texture, &form, &acc, &w, &h);
                format = form;
                access = acc;
                this->w = w;
                this->h = h;
            }
        }

        SDL_Texture * Texture::getTexture()
        {
            return texture;
        }

        Sint32 Texture::getWidth()
        {
            return w;
        }

        Sint32 Texture::getHeight()
        {
            return h;
        }

        SDL_Rect Texture::getSize()
        {
            SDL_Rect r = {};
            r.x = 0;
            r.y = 0;
            r.w = w;
            r.h = h;
            return r;
        }

        Texture &Texture::setBlendMode(SDL_BlendMode mode)
        {
            SDL_SetTextureBlendMode(texture, mode);
            return *this;
        }

        SDL_BlendMode Texture::getBlendMode()
        {
            SDL_BlendMode mode;
            SDL_GetTextureBlendMode(texture, &mode);
            return mode;
        }

        Texture &Texture::setAlphaMod(Uint8 alpha_mod)
        {
            SDL_SetTextureAlphaMod(texture, alpha_mod);
            return *this;
        }

        Uint8 Texture::getAlphaMod()
        {
            Uint8 mod;
            SDL_GetTextureAlphaMod(texture, &mod);
            return mod;
        }

        Texture &Texture::setColorMod(SDL_Color color_mod)
        {
            SDL_SetTextureColorMod(texture, color_mod.r, color_mod.g, color_mod.r);
            return *this;
        }

        SDL_Color Texture::getColorMod()
        {
            SDL_Color mod;
            SDL_GetTextureColorMod(texture, &mod.r, &mod.g, &mod.b);
            return mod;
        }
    }
}