#ifndef TURBO_MEDIA_PLAYER_H
#define TURBO_MEDIA_PLAYER_H

#include <vector>

#include "audio/audio_def.h"
#include "audio/music.h"
#include "system/time.h"
#include "util/dir.h"

namespace TURBO
{
    namespace AUDIO
    {
        class MediaPlayer
        {
        private:
            SYSTEM::Timer position;
            Uint8 volume;
            std::string path;
            std::vector<Music*> playlist;
            Music *current_medium;

            void finished();

        public:
            explicit MediaPlayer(std::string path);
            ~MediaPlayer();
            MEDIUM_STATE getState() const;
            void onFinish(void * callback);
            void onMediaChanged(void * callback);
            void onPositionChanged(void * callback);
            void onStateChanged(void * callback);
            void onVolumeChanged(void * callback);
            bool playing();
            bool paused();
            Uint8 setVolume(Uint8 volume);
            Uint8 getVolume() const;

            /**
             *
             * @return the current medium position
             */
            Uint32 getPosition();

            /**
             * Sets the current medium to the given position.
             * @param position the new position in the music obejct as milliseconds
             * @return the current medium position
             */
            Uint32 setPosition(Uint32 position);
            MEDIUM_STATE rewind();
            MEDIUM_STATE play();
            MEDIUM_STATE pause();
            MEDIUM_STATE resume();
            MEDIUM_STATE stop();
            std::vector<Music*> addToPlaylist(Music *music, int index = -1);
            std::vector<Music*> removeFromPlaylist(Music *music);
            std::vector<Music*> removeFromPlaylist(int index);
            std::vector<Music*> getPlaylist() const;
            Uint64 getPlaylistSize() const;
            Music *setMedium(Music *music);
            Music *getMedium() const;
            std::string setPlaylistLocation(std::string path);
            std::string getPlaylistLocation() const;
        };
    }
}

#endif //TURBO_MEDIA_PLAYER_H
