#include <util/dir.h>
#include "video/window.h"
#include "video/opengl.h"

namespace TURBO
{
    namespace VIDEO
    {
        bool OpenGL::GL_IS_INIT = false;
        bool OpenGL::GLEW_IS_INIT = false;

        void OpenGL::init()
        {
            if(glewInit())
            {
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, TURBO_GL_MAJOR);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, TURBO_GL_MINOR);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                SDL_GL_SetSwapInterval(1);
                OpenGL::GLEW_IS_INIT = true;
                OpenGL::GL_IS_INIT = true;
            }
        }

        void OpenGL::swap(Window &window)
        {
            SDL_GL_SwapWindow(window.Get());
        }

        void OpenGL::clear(GLbitfield mask)
        {
            glClear(mask);
        }
    }
}