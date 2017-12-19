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
            std::string path;
            MEDIUM_STATE state;
            Mix_Music * music;
            Mix_MusicType type;

        public:
            explicit Music(std::string path);
            ~Music();
            Mix_Music * getMusic();
            Mix_Music * setMusic(std::string path);
            Mix_MusicType getType();
            MEDIUM_STATE getState();
            MEDIUM_STATE rewind();
            MEDIUM_STATE play(Uint32 fadein_ms = 0);
            MEDIUM_STATE pause();
            MEDIUM_STATE resume();
            MEDIUM_STATE stop(Uint32 fadeout_ms = 0);
        };
    }
}

#endif //TURBO_MUSIC_H
