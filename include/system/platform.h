#ifndef TURBO_PLATFORM_H
#define TURBO_PLATFORM_H

#include "system/system_def.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class Platform
        {
        public:
            Platform() = delete;
            static std::string getPlatform();
            static Sint32 getAudioDevices();
            static Sint32 getAudioDrivers();
            static Sint32 getDisplayModes();
            static Sint32 getVideoDisplays();
            static Sint32 getVideoDrivers();
            static Sint32 getCpuLogical();
            static Sint32 getCpuCacheSize();
            static Sint32 getRam();
        };
    }
}

#endif //TURBO_PLATFORM_H
