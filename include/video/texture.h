#ifndef TURBO_TEXTURE_H
#define TURBO_TEXTURE_H

#include "video/video_def.h"
#include "system/sdl.h"
#include "util/log.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Texture
        {
        private:
            SDL_Renderer *renderer;
            SDL_Texture  *texture;
            Sint32 w;
            Sint32 h;
            Uint32 format;
            Sint32 access;

        public:
            /**
             * Creates an empty texture.
             * @param renderer  a pointer to the renderer
             * @param w         width of the texture
             * @param h         height of the texture
             * @param format    format of the texture
             * @param access    access of the texture
             */
            Texture(SDL_Renderer *renderer, Sint32 w, Sint32 h, Uint32 format = TURBO_SDL_TEXTURE_FORMAT,
                    Sint32 access = TURBO_SDL_TEXTURE_ACCESS);

            /**
             * Creates an empty texture.
             * @param renderer a pointer to the sdl renderer
             * @param surface a pointer to the sdl surface
             */
            Texture(SDL_Renderer *renderer, SDL_Surface *surface);

            /**
             * Reloads texture infos.
             */
            void loadTextureInfo();

            SDL_Texture *getTexture();

            Sint32 getWidth();

            Sint32 getHeight();

            SDL_Rect getSize();
        };
    }
}

#endif //TURBO_TEXTURE_H
