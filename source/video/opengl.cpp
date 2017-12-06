#include <util/dir.h>
#include "video/window.h"
#include "video/opengl.h"

namespace TURBO
{
    namespace VIDEO
    {
        void OpenGL::init()
        {
            glewInit();
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, TURBO_GL_MAJOR);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, TURBO_GL_MINOR);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetSwapInterval(1);
        }

        void OpenGL::swap(Window &window)
        {
            SDL_GL_SwapWindow(window.Get());
        }

        void OpenGL::clear(GLbitfield mask)
        {
            glClear(mask);
        }

        Uint32 OpenGL::loadShader(const std::string file, const GLenum shader_type)
        {
            std::string content = UTIL::File::getFileContents(file);
            const char * str = content.c_str();
            GLuint shader = glCreateShader(shader_type);
            glShaderSource(shader, 1, &str, NULL);
            glCompileShader(shader);
            return shader;
        }
    }
}