#include "system/platform.h"

namespace TURBO
{
    namespace SYSTEM
    {
        void Platform::setEnvironment(std::string var, std::string path, bool override)
        {
            setenv(var.c_str(), path.c_str(), override ? 1 : 0);
        }

        std::string Platform::getPlatform()
        {
            return SDL_GetPlatform();
        }

        Sint32 Platform::getAudioDevices()
        {
            return SDL_GetNumAudioDevices(0);
        }

        Sint32 Platform::getAudioDrivers()
        {
            return SDL_GetNumAudioDrivers();
        }

        Sint32 Platform::getDisplayModes()
        {
            return SDL_GetNumDisplayModes(0);
        }

        Sint32 Platform::getVideoDisplays()
        {
            return SDL_GetNumVideoDisplays();
        }

        Sint32 Platform::getVideoDrivers()
        {
            return SDL_GetNumVideoDrivers();
        }

        Sint32 Platform::getCpuLogical()
        {
            return SDL_GetCPUCount();
        }

        Sint32 Platform::getCpuCacheSize()
        {
            return SDL_GetCPUCacheLineSize();
        }

        Sint32 Platform::getRam()
        {
            return SDL_GetSystemRAM();
        }
    }
}