#ifndef TURBO_TURBO_DEF_H
#define TURBO_TURBO_DEF_H

#include <string>

#include <SDL_pixels.h>
#include <SDL_render.h>

namespace TURBO
{
    const Uint32 TURBO_GL_MAJOR = 3;
    const Uint32 TURBO_GL_MINOR = 3;

    const Uint32 TURBO_SDL_TEXTURE_FORMAT = SDL_PIXELFORMAT_ARGB8888;
    const Uint32 TURBO_SDL_TEXTURE_ACCESS = SDL_TEXTUREACCESS_STATIC;

    const std::string TURBO_RESOURCE_PATH = "./resources/";
    const std::string TURBO_SETTINGS_PATH = TURBO_RESOURCE_PATH + "application/";
    const std::string TURBO_FONT_PATH = TURBO_SETTINGS_PATH + "fonts/";

    const std::string TURBO_DEFAULT_SETTINGS = TURBO_SETTINGS_PATH + "application.ini";
    const std::string TURBO_DEFAULT_FONT = TURBO_FONT_PATH + "OpenSans-Light.ttf";
    const Uint8 TURBO_DEFAULT_FONT_SIZE = 32;
}

#endif //TURBO_TURBO_DEF_H
