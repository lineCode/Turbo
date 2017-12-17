#ifndef TURBO_MUSIC_H
#define TURBO_MUSIC_H

#include "SDL_audio.h"
#include "SDL_mixer.h"

#include "audio/audio_def.h"
#include "util/file.h"

namespace TURBO
{
    namespace AUDIO
    {
        class Music
        {
        private:
            Mix_Music * music;
            Mix_MusicType type;
            std::string path;

        public:
            explicit Music(std::string path);
            ~Music();
            Mix_Music * getMusic();
        };
    }
}

#endif //TURBO_MUSIC_H
