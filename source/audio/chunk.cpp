#include "audio/chunk.h"

namespace TURBO
{
    namespace AUDIO
    {
        Chunk::Chunk(std::string path)
            : path(path),
              state(MEDIUM_STATE::STOPPED)
        {
            if(UTIL::File::isType(path, "wav"))
            {
                chunk = Mix_LoadWAV(path.c_str());
            }
        }

        Chunk::~Chunk()
        {
            Mix_FreeChunk(chunk);
        }

        Mix_Chunk *Chunk::getChunk()
        {
            return chunk;
        }

        Mix_Chunk *Chunk::setChunk(std::string path)
        {
            if(UTIL::File::isType(path, "wav"))
            {
                this->path = path;
                chunk = Mix_LoadWAV(path.c_str());
            }
            return chunk;
        }

        MEDIUM_STATE Chunk::getState()
        {
            return state;
        }

        MEDIUM_STATE Chunk::play(Uint32 fadein_ms)
        {
            if(state == MEDIUM_STATE::STOPPED)
            {
                if(fadein_ms > 0)
                {
                    if(Mix_FadeInChannel(-1, chunk, 0, fadein_ms) != -1)
                    {
                        state = MEDIUM_STATE::PLAYING;
                    }
                }
                else
                {
                    if(Mix_PlayChannel(-1, chunk, 0) != -1)
                    {
                        state = MEDIUM_STATE::PLAYING;
                    }
                }
            }
            return state;
        }

        MEDIUM_STATE Chunk::pause()
        {
            if(state == MEDIUM_STATE::PLAYING)
            {
                Mix_Pause(-1);
                state = MEDIUM_STATE::PAUSED;
            }
            return state;
        }

        MEDIUM_STATE Chunk::resume()
        {
            if(state == MEDIUM_STATE::PAUSED)
            {
                Mix_Resume(-1);
                state = MEDIUM_STATE::PLAYING;
            }
            return state;
        }

        MEDIUM_STATE Chunk::stop(Uint32 fadeout_ms)
        {
            if(state != MEDIUM_STATE::STOPPED)
            {
                if(fadeout_ms > 0)
                {
                    Mix_FadeOutChannel(-1, fadeout_ms);
                }
                else
                {
                    Mix_HaltChannel(-1);
                }
                state = MEDIUM_STATE::STOPPED;
            }
            return state;
        }
    }
}