#ifndef TURBO_MUSIC_H
#define TURBO_MUSIC_H

#include "SDL_audio.h"
#include "SDL_mixer.h"

#include "audio/audio_def.h"
#include "system/sdl.h"
#include "util/file.h"
#include "util/log.h"

namespace TURBO
{
    namespace AUDIO
    {
        class Music
        {
        private:
            std::string   path;
            MEDIUM_STATE  state;
            Mix_Music    *music;
            Mix_MusicType music_type;

        public:
            /**
             * Initializes the music with the path to the file.
             * @param path the path to the music
             */
            explicit Music(std::string path);

            ~Music();

            /**
             * Returns the handle to the music.
             * @return the music handle
             */
            Mix_Music *getMusic() const;

            /**
             * Sets the new path to the music.
             * @param path the new path
             * @return the music handle
             */
            Mix_Music *setMusic(std::string path);

            /**
             * Returns the path to the music.
             * @return the music path
             */
            std::string getPath() const;

            /**
             * Returns the type of the music.
             * @return the type of the music
             */
            Mix_MusicType getType() const;

            /**
             * Returns the state of the music.
             * @return the state of the music
             */
            MEDIUM_STATE getState() const;

            /**
             * Sets the state of the medium.
             * @param state the new state
             * @return the state of the music
             */
            MEDIUM_STATE setState(MEDIUM_STATE state);

            /**
             * Rewinds the music to the start.
             * @return the state of the music
             */
            MEDIUM_STATE rewind();

            /**
             * Stats to play the music.
             * @param fadein_ms milliseconds of the fade in effect
             * @return the state of the music
             */
            MEDIUM_STATE play(Uint32 fadein_ms = 0);

            /**
             * Pauses the music.
             * @return the state of the music
             */
            MEDIUM_STATE pause();

            /**
             * Resumes the music.
             * @return the state of the music
             */
            MEDIUM_STATE resume();

            /**
             * Stops the music.
             * @param fadeout_ms milliseconds of the fade out effect
             * @return the state of the music
             */
            MEDIUM_STATE stop(Uint32 fadeout_ms = 0);
        };
    }
}

#endif //TURBO_MUSIC_H
