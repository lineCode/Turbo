#include "video/texture.h"

namespace TURBO
{
    namespace VIDEO
    {
        Texture::Texture(SDL_Renderer *renderer, Sint32 w, Sint32 h, Uint32 format, Sint32 access)
            : renderer(renderer), w(w), h(h), format(format), access(access)
        {
            texture = SDL_CreateTexture(renderer, format, access, w, h);
            loadTextureInfo();
        }

        Texture::Texture(SDL_Renderer *renderer, SDL_Surface *surface)
            : renderer(renderer)
        {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            loadTextureInfo();
        }

        void Texture::loadTextureInfo()
        {
            Sint32 w = 0, h = 0, a = 0;
            Uint32 f = 0;

            if(texture != nullptr)
            {
                SDL_QueryTexture(texture, &f, &a, &w, &h);
                format = f;
                access = a;
                this->w = w;
                this->h = h;
            }
        }

        SDL_Texture * Texture::getTexture()
        {
            return texture;
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
    }
}