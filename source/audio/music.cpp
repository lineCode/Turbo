#include "audio/music.h"

namespace TURBO
{
    namespace AUDIO
    {
        Music::Music(const std::string path)
            : path(path)
        {
            if(UTIL::File::hasFilter(path, std::vector<std::string>{"mp3", "ogg"}))
            {
                music = Mix_LoadMUS(path.c_str());
                type = Mix_GetMusicType(music);
            }
        }

        Music::~Music()
        {
            Mix_FreeMusic(music);
        }

        Mix_Music * Music::getMusic()
        {
            return music;
        }
    }
}