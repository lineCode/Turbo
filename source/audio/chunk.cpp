#include "audio/chunk.h"

namespace TURBO
{
    namespace AUDIO
    {
        Chunk::Chunk(std::string path)
            : path(path)
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

        Mix_Chunk * Chunk::getChunk()
        {
            return chunk;
        }
    }
}