#ifndef TURBO_TURBO_DEF_H
#define TURBO_TURBO_DEF_H

#include <string>

#include <SDL_pixels.h>
#include <SDL_render.h>

namespace TURBO
{
    /**
     * TURBO Resource Paths and Files
     */
    const std::string TURBO_RESOURCE_PATH        = "./resources/";
    const std::string TURBO_AUDIO_PATH           = TURBO_RESOURCE_PATH + "audio/";
    const std::string TURBO_FONT_PATH            = TURBO_RESOURCE_PATH + "font/";
    const std::string TURBO_IMAGE_PATH           = TURBO_RESOURCE_PATH + "image/";
    const std::string TURBO_SCRIPT_PATH          = TURBO_RESOURCE_PATH + "script/";
    const std::string TURBO_LUA_SCRIPT_PATH      = TURBO_LUA_SCRIPT_PATH + "lua/";
    const std::string TURBO_PYTHON_SCRIPT_PATH   = TURBO_PYTHON_SCRIPT_PATH + "python/";
    const std::string TURBO_SETTINGS_PATH        = TURBO_RESOURCE_PATH + "turbo/";
    const std::string TURBO_SETTINGS_FONT_PATH   = TURBO_SETTINGS_PATH + "font/";
    const std::string TURBO_SETTINGS_DATA_PATH   = TURBO_SETTINGS_PATH + "data/";
    const std::string TURBO_SETTINGS_SHADER_PATH = TURBO_SETTINGS_PATH + "shader/";
    const std::string TURBO_DEFAULT_SETTINGS     = TURBO_SETTINGS_PATH + "turbo.ini";

    /**
     * TURBO Default Variables
     */
    const std::string TURBO_DEFAULT_FONT      = TURBO_FONT_PATH + "OpenSans-Light.ttf";
    const Uint8       TURBO_DEFAULT_FONT_SIZE = 32;
}

#endif //TURBO_TURBO_DEF_H
