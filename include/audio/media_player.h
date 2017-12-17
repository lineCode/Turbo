#ifndef TURBO_MEDIA_PLAYER_H
#define TURBO_MEDIA_PLAYER_H

#include <vector>

#include "audio/audio_def.h"
#include "audio/music.h"

namespace TURBO
{
    namespace AUDIO
    {
        class MediaPlayer
        {
        private:
            PLAYER_STATE state;
            std::vector<Music&> playlist;

            Music & current_medium;

        public:
            PLAYER_STATE getState() const;
            PLAYER_STATE play();
            PLAYER_STATE pause();
            PLAYER_STATE resume();
            PLAYER_STATE stop();
            std::vector<Music&> addToPlaylist(Music &music, int index = -1);
            std::vector<Music&> removeFromPlaylist(Music &music);
            std::vector<Music&> removeFromPlaylist(int index);
            std::vector<Music&> getPlaylist() const;
            Uint64 getPlaylistSize() const;
            Music &setMedium(Music &music);
            Music &getMedium() const;
        };
    }
}

#endif //TURBO_MEDIA_PLAYER_H
