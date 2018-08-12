#include "audio/music.h"

namespace TURBO
{
    namespace AUDIO
    {
        Music::Music(const std::string path)
            : path(path),
              state(MEDIUM_STATE::STOPPED)
        {
            setMusic(path);
        }

        Music::~Music()
        {
            if(music != nullptr)
            {
                stop();
                Mix_FreeMusic(music);
                music = nullptr;
            }
        }

        Mix_Music * Music::getMusic() const
        {
            return music;
        }

        Mix_Music * Music::setMusic(const std::string path)
        {
            if(SYSTEM::SDL::MIX_IS_INIT)
            {
                if(UTIL::File::hasFilter(path, std::vector<std::string>{"mp3", "ogg", "flac"}))
                {
                    if(UTIL::Dir::fileExists(path))
                    {
                        music = Mix_LoadMUS(path.c_str());
                        if(music != nullptr)
                        {
                            music_type = Mix_GetMusicType(music);
                            this->path = path;
                        }
                    }
                }
            }
            else
            {
                UTIL::Log::err("SDL_MIX is not initialized");
            }
            return music;
        }

        std::string Music::getPath() const
        {
            return path;
        }

        Mix_MusicType Music::getType() const
        {
            return music_type;
        }

        MEDIUM_STATE Music::getState() const
        {
            return state;
        }

        MEDIUM_STATE Music::setState(MEDIUM_STATE state)
        {
            if(state == MEDIUM_STATE::PLAYING)
            {
                if(this->state == MEDIUM_STATE::PAUSED)
                {
                    resume();
                }
                else
                {
                    play();
                }
            }
            else if(state == MEDIUM_STATE::PAUSED)
            {
                pause();
            }
            else if(state == MEDIUM_STATE::STOPPED)
            {
                stop();
            }
        }

        MEDIUM_STATE Music::rewind()
        {
            if(music_type >= Mix_MusicType::MUS_MOD && music_type <= Mix_MusicType::MUS_MP3)
            {
                if(music != nullptr)
                {
                    Mix_RewindMusic();
                }
            }
            return state;
        }

        MEDIUM_STATE Music::play(Uint32 fadein_ms)
        {
            if(state == MEDIUM_STATE::STOPPED && music != nullptr)
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
            if(state == MEDIUM_STATE::PLAYING && music != nullptr)
            {
                Mix_PauseMusic();
                state = MEDIUM_STATE::PAUSED;
            }
            return state;
        }

        MEDIUM_STATE Music::resume()
        {
            if(state == MEDIUM_STATE::PAUSED && music != nullptr)
            {
                Mix_ResumeMusic();
                state = MEDIUM_STATE::PLAYING;
            }
            return state;
        }


        MEDIUM_STATE Music::stop(Uint32 fadeout_ms)
        {
            if(state != MEDIUM_STATE::STOPPED && music != nullptr)
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