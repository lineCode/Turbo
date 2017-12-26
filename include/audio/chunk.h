#ifndef TURBO_CHUNK_H
#define TURBO_CHUNK_H

#include "SDL_audio.h"
#include "SDL_mixer.h"

#include "audio/audio_def.h"
#include "util/file.h"

namespace TURBO
{
    namespace AUDIO
    {
        class Chunk
        {
        private:
            Mix_Chunk *chunk;
            Sint8 channel;
            std::string path;
            MEDIUM_STATE state;

        public:
            explicit Chunk(std::string path, Sint8 channel = -1);
            ~Chunk();
            Mix_Chunk *getChunk() const;
            Mix_Chunk *setChunk(std::string path);
            std::string getPath() const;
            Sint8 getChannel() const;
            Sint8 setChannel(Sint8 channel);
            MEDIUM_STATE getState() const;
            MEDIUM_STATE play(Uint32 fadein_ms = 0);
            MEDIUM_STATE pause();
            MEDIUM_STATE resume();
            MEDIUM_STATE stop(Uint32 fadeout_ms = 0);
        };
    }
}

#endif //TURBO_CHUNK_H
