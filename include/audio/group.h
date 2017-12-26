#ifndef TURBO_GROUP_H
#define TURBO_GROUP_H

#include <vector>

#include "audio_def.h"

namespace TURBO
{
    namespace AUDIO
    {
        class Group
        {
        private:
            Uint8 id;
            std::vector<Uint8> channels;
            
        public:
            Group(Uint8 id, Uint8 channels);
            Group(Uint8 id, Uint8 start, Uint8 stop);
            static Sint32 reserveChannels(Uint32 channels);
            static Sint32 unreserveChannels();
            Uint8 getId();
            std::vector<Uint8> getChannels();
        };
    }
}

#endif //TURBO_GROUP_H
