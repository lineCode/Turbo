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
            std::string path;
            std::map<Uint8, std::function<void()>> callbacks;
            std::vector<Music*> playlist;
            Music *current_medium;
            Uint64 playlist_position;
            Uint8 volume;
            Uint8 last_mute_volume;
            bool shuffle_on;
            bool repeat_on;

            /**
             * Executes a callback function if any is connected with the given event.
             * @param event type of the event
             */
            void fireCallback(Uint8 event);

        public:
            /**
             * Initializes a media player with audio track from the given path.
             */
            explicit MediaPlayer(std::string path);

            /**
             * Frees all alocated music objects.
             */
            ~MediaPlayer();

            /**
             *
             * @return the state of the current medium.
             */
            MEDIUM_STATE getState() const;

            /**
             * Registers a callback function that will fire if the given event occours.
             * @param event type of the event to register
             * @param callback the callback function that gets called when the event is triggered
             */
            void registerCallback(Uint8 event, std::function<void()> callback);
            bool isPlaying();
            bool isPaused();
            Uint8 setVolume(Uint8 volume);
            Uint8 getVolume() const;
            Uint8 setMute(bool mute);
            bool isMuted() const;

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
            Music *next();
            Music *previous();
            bool setShuffle(bool shuffle);
            bool getShuffle();
            bool setRepeat(bool repeat);
            bool getRepeat();
            std::vector<Music*> addToPlaylist(Music *music, int index = -1);
            std::vector<Music*> removeFromPlaylist(Music *music);
            std::vector<Music*> removeFromPlaylist(int index);
            std::vector<Music*> getPlaylist() const;
            Uint64 getPlaylistSize() const;
            Uint64 getPlaylistPosition() const;
            Uint64 setPlaylistPosition(Uint64 pos);
            Music *getMedium() const;
            std::string setPlaylistPath(std::string path);
            std::string getPlaylistPath() const;
        };
    }
}

#endif //TURBO_MEDIA_PLAYER_H
