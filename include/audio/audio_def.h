#ifndef TURBO_AUDIO_DEF_H
#define TURBO_AUDIO_DEF_H

#include <vector>

#include "SDL_mixer.h"

#include "turbo_def.h"

namespace TURBO
{
    namespace AUDIO
    {
        const std::vector<std::string> AUDIO_EXTENSIONS{"NONE", "CMD", "WAV", "MOD", "MID", "OGG",
                                                        "MP3", "MP3_MAD", "FLAC", "MODPLUG"};
        const std::vector<std::string> MUSIC_EXTENSIONS{"MP3", "OGG", "FLAC", "MID", "MOD"};

        const Uint8 MIN_VOLUME = 0;
        const Uint8 MAX_VOLUME = MIX_MAX_VOLUME;

        enum MEDIUM_STATE : Uint8
        {
            STOPPED = 0x0,
            PLAYING = 0x1,
            PAUSED  = 0x2,
        };

        enum EVENT_TYPE : Uint8
        {
            ON_PLAY = 0x0,
            ON_PAUSE,
            ON_RESUME,
            ON_STOP,
            ON_REWIND,
            ON_FINISH,
            ON_POSITION_CHANGED,
            ON_VOLUME_CHANGED,
            ON_MEDIUM_CHANGED,
            ON_PLAYLIST_CHANGED,
            ON_MUTE,
            ON_UNMUTE
        };
    }
}

#endif //TURBO_AUDIO_DEF_H
