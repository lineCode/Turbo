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
            Mix_Chunk * chunk;
            std::string path;

        public:
            explicit Chunk(std::string path);
            ~Chunk();
            Mix_Chunk * getChunk();
        };
    }
}

#endif //TURBO_CHUNK_H
