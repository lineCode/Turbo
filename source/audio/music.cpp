#include "audio/music.h"

namespace TURBO
{
    namespace AUDIO
    {
        Music::Music(const std::string path)
            : path(path),
              state(MEDIUM_STATE::STOPPED)
        {
            if(UTIL::File::hasFilter(path, std::vector<std::string>{"mp3", "ogg", "flac"}))
            {
                music = Mix_LoadMUS(path.c_str());
                type = Mix_GetMusicType(music);
            }
        }

        Music::~Music()
        {
            if(music != nullptr)
            {
                Mix_FreeMusic(music);
            }
        }

        Mix_Music * Music::getMusic()
        {
            return music;
        }

        Mix_Music * Music::setMusic(const std::string path)
        {
            if(UTIL::File::hasFilter(path, std::vector<std::string>{"mp3", "ogg", "flac"}))
            {
                music = Mix_LoadMUS(path.c_str());
                type = Mix_GetMusicType(music);
            }
            return music;
        }

        Mix_MusicType Music::getType()
        {
            return type;
        }

        MEDIUM_STATE Music::getState()
        {
            return state;
        }

        MEDIUM_STATE Music::rewind()
        {
            if(type == Mix_MusicType::MUS_MOD || type == Mix_MusicType::MUS_OGG ||
                type == Mix_MusicType::MUS_MP3 || type == Mix_MusicType::MUS_MID)
            {
                stop();
                Mix_RewindMusic();
                state = MEDIUM_STATE::STOPPED;
            }
            return state;
        }

        MEDIUM_STATE Music::play(Uint32 fadein_ms)
        {
            if(state == MEDIUM_STATE::STOPPED)
            {
                if(fadein_ms > 0)
                {
                    Mix_FadeInMusic(music, 0, fadein_ms);
                }
                else
                {
                    Mix_PlayMusic(music, 0);
                }
                state = MEDIUM_STATE::PLAYING;
            }
            return state;
        }

        MEDIUM_STATE Music::pause()
        {
            if(state == MEDIUM_STATE::PLAYING)
            {
                Mix_PauseMusic();
                state = MEDIUM_STATE::PAUSED;
            }
            return state;
        }

        MEDIUM_STATE Music::resume()
        {
            if(state == MEDIUM_STATE::PAUSED)
            {
                Mix_ResumeMusic();
                state = MEDIUM_STATE::PLAYING;
            }
            return state;
        }

        MEDIUM_STATE Music::stop(Uint32 fadeout_ms)
        {
            if(state != MEDIUM_STATE::STOPPED)
            {
                if(fadeout_ms > 0)
                {
                    Mix_FadeOutMusic(fadeout_ms);
                }
                else
                {
                    Mix_HaltMusic();
                }
                state = MEDIUM_STATE::STOPPED;
            }
            return state;
        }
    }
}