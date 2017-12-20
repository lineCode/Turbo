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
            std::string path;
            MEDIUM_STATE state;

        public:
            explicit Chunk(std::string path);
            ~Chunk();
            Mix_Chunk *getChunk();
            Mix_Chunk *setChunk(std::string path);
            MEDIUM_STATE getState();
            MEDIUM_STATE play(Uint32 fadein_ms = 0);
            MEDIUM_STATE pause();
            MEDIUM_STATE resume();
            MEDIUM_STATE stop(Uint32 fadeout_ms = 0);
        };
    }
}

#endif //TURBO_CHUNK_H
