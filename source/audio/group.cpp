#include "audio/group.h"

namespace TURBO
{
    namespace AUDIO
    {
        Group::Group(Uint8 id, Uint8 channels)
            : id(id)
        {
            for(int i = 0; i < channels; ++i)
            {
                if(Mix_GroupChannel(i, id))
                {
                    this->channels.push_back(i);
                }
            }
        }

        Group::Group(Uint8 id, Uint8 start, Uint8 stop)
        {
            if(start > stop)
            {
                std::swap(start, stop);
            }

            for(int i = start; i < stop; ++i)
            {
                if(Mix_GroupChannel(i, id))
                {
                    this->channels.push_back(i);
                }
            }
        }

        Sint32 Group::reserveChannels(Uint32 channels)
        {
            if(channels > 0xFF)
            {
                return Mix_ReserveChannels(0xFF);
            }
            else
            {
                return Mix_ReserveChannels(channels);
            }
        }

        Sint32 Group::unreserveChannels()
        {
            return Mix_ReserveChannels(0);
        }

        Uint8 Group::getId()
        {
            return id;
        }

        std::vector<Uint8> Group::getChannels()
        {
            return channels;
        }
    }
}