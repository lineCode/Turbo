#ifndef TURBO_OPENGL_H
#define TURBO_OPENGL_H

#include <GL/glew.h>
#include <SDL_opengl.h>

#include "video/video_def.h"
#include "system/sdl.h"
#include "util/log.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Window;

        /**
         * Wraps OpenGL functions from SDL.
         */
        class OpenGL
        {
        public:
            static bool GLEW_IS_INIT;

            static void init();

            static void swap(Window &window);

            static void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT);
        };
    }
}

#endif //TURBO_OPENGL_H
