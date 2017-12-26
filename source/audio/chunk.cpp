#include "audio/chunk.h"

namespace TURBO
{
    namespace AUDIO
    {
        Chunk::Chunk(std::string path, Sint8 channel)
            : channel(channel), 
              path(path),
              state(MEDIUM_STATE::STOPPED)
        {
            if(UTIL::File::isType(path, "wav"))
            {
                chunk = Mix_LoadWAV(path.c_str());
                setChannel(channel);
            }
        }

        Chunk::~Chunk()
        {
            Mix_FreeChunk(chunk);
        }

        Mix_Chunk *Chunk::getChunk() const
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

        std::string Chunk::getPath() const
        {
            return path;
        }

        Sint8 Chunk::getChannel() const
        {
            return channel;
        }

        Sint8 Chunk::setChannel(Sint8 channel)
        {
            if(channel < -1)
            {
                this->channel = -1;
            }
            else
            {
                this->channel = channel;
            }
            return this->channel;
        }

        MEDIUM_STATE Chunk::getState() const
        {
            return state;
        }

        MEDIUM_STATE Chunk::play(Uint32 fadein_ms)
        {
            if(state == MEDIUM_STATE::STOPPED && chunk != nullptr)
            {
                if(fadein_ms > 0)
                {
                    if(Mix_FadeInChannel(channel, chunk, 0, fadein_ms) != -1)
                    {
                        state = MEDIUM_STATE::PLAYING;
                    }
                }
                else
                {
                    if(Mix_PlayChannel(channel, chunk, 0) != -1)
                    {
                        state = MEDIUM_STATE::PLAYING;
                    }
                }
            }
            return state;
        }

        MEDIUM_STATE Chunk::pause()
        {
            if(state == MEDIUM_STATE::PLAYING && chunk != nullptr)
            {
                Mix_Pause(channel);
                state = MEDIUM_STATE::PAUSED;
            }
            return state;
        }

        MEDIUM_STATE Chunk::resume()
        {
            if(state == MEDIUM_STATE::PAUSED && chunk != nullptr)
            {
                Mix_Resume(channel);
                state = MEDIUM_STATE::PLAYING;
            }
            return state;
        }

        MEDIUM_STATE Chunk::stop(Uint32 fadeout_ms)
        {
            if(state != MEDIUM_STATE::STOPPED && chunk != nullptr)
            {
                if(fadeout_ms > 0)
                {
                    Mix_FadeOutChannel(channel, fadeout_ms);
                }
                else
                {
                    Mix_HaltChannel(channel);
                }
                state = MEDIUM_STATE::STOPPED;
            }
            return state;
        }
    }
}