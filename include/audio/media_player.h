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
            SYSTEM::Timer                          position;
            std::string                            path;
            std::map<Uint8, std::function<void()>> callbacks;
            std::vector<Music *>                   playlist;
            Music                                  *current_medium;
            Uint64                                 playlist_position;
            Uint8                                  volume;
            Uint8                                  last_mute_volume;
            bool                                   shuffle_on;
            bool                                   repeat_on;

            /**
             * Executes a callback function if any is connected with the given event.
             * @param event type of the event
             */
            void fireCallback(Uint8 event);

        public:
            /**
             * Initializes a media player with audio track from the given path.
             * @param path the path of the playlist
             */
            explicit MediaPlayer(std::string path);

            /**
             * Frees all allocated music objects.
             */
            ~MediaPlayer();

            /**
             * Returns the state of the current medium.
             * @return the state of the current medium.
             */
            MEDIUM_STATE getState() const;

            /**
             * Registers a callback function that will fire if the given event occours.
             * @param event type of the event to register
             * @param callback the callback function that gets called when the event is triggered
             */
            void registerCallback(Uint8 event, std::function<void()> callback);

            /**
             * Returns true if the media player is playing.
             * @return true if media player is playing
             */
            bool isPlaying();

            /**
             * Returns true if media player is paused.
             * @return true if media player is paused
             */
            bool isPaused();

            /**
             * Sets the volume of the media player. Valid range is from 0 (mute) to 255.
             * @param volume the loudness of the playback
             * @return the volume of the media player
             */
            Uint8 setVolume(Uint8 volume);

            /**
             * Return the volume of the media player.
             * @return the volume of the media player
             */
            Uint8 getVolume() const;

            /**
             * Sets the state of the volume.
             * @param mute state of the volume
             * @return the volume of the media player
             */
            Uint8 setMute(bool mute);

            /**
             * Returns true if the volume of the media player is bigger than 0.
             * @return true if the volume of the media player is bigger than 0
             */
            bool isMuted() const;

            /**
             * Returns the position of the current medium.
             * @return the current medium position
             */
            Uint32 getPosition();

            /**
             * Sets the current medium to the given position.
             * @param position the new position in the music object in milliseconds
             * @return the current medium position or 0 on failure
             */
            Uint32 setPosition(Uint32 position);

            /**
             * Restart the current medium from the beginning.
             * @return the state of the medium player
             */
            MEDIUM_STATE rewind();

            /**
             * Sets the player to play or pause.
             * @param play
             * @return the new state of the medium player
             */
            MEDIUM_STATE setPlayback(bool play);

            /**
             * Sets the player to play or pause depending on the current medium state.
             * @return the new state of the medium player
             */
            MEDIUM_STATE togglePlayback();

            /**
             * Plays the current medium.
             * @return the state of the medium player
             */
            MEDIUM_STATE play();

            /**
             * Pauses the current medium.
             * @return the state of the medium player
             */
            MEDIUM_STATE pause();

            /**
             * Resumes the current medium.
             * @return the state of the medium player
             */
            MEDIUM_STATE resume();

            /**
             * Stops the current medium.
             * @return the state of the medium player
             */
            MEDIUM_STATE stop();

            /**
             * Sets the current medium to the next element in the playlist.
             * @return the pointer to the medium
             */
            Music *next();

            /**
             * Sets the current medium to the previous element in the playlist.
             * @return the pointer to the medium
             */
            Music *previous();

            /**
             * Sets the state of shuffle.
             * @param shuffle the new shuffle state
             * @return the shuffle state
             */
            bool setShuffle(bool shuffle);

            /**
             * Returns the state of the shuffle.
             * @return the shuffle state
             */
            bool getShuffle();

            /**
             * Sets the state of repeat
             * @param repeat the new repeat state
             * @return the repeat state
             */
            bool setRepeat(bool repeat);

            /**
             * Returns the state of repeat
             * @return the repeat state
             */
            bool getRepeat();

            /**
             * Adds a medium to the playlist.
             * @param music the medium
             * @param index the position of the medium in the playlist
             * @return the whole playlist
             */
            std::vector<Music *> addToPlaylist(Music *music, int index = -1);

            /**
             * Removes a medium to the playlist.
             * @param music the medium
             * @return the whole playlist
             */
            std::vector<Music *> removeFromPlaylist(Music *music);

            /**
             * Removes a medium to the playlist.
             * @param index the position of the medium in the playlist
             * @return the whole playlist
             */
            std::vector<Music *> removeFromPlaylist(int index);

            /**
             * Returns the playlist.
             * @return the whole playlist
             */
            std::vector<Music *> getPlaylist() const;

            /**
             * Returns the number of elements in the playlist.
             * @return size of the playlist
             */
            Uint64 getPlaylistSize() const;

            /**
             * Returns the current position of the current medium in the playlist.
             * @return the position of the current medium
             */
            Uint64 getPlaylistPosition() const;

            /**
             * Sets the playlist position.
             * @param pos the new position of the playlist
             * @return the position of the current medium
             */
            Uint64 setPlaylistPosition(Uint64 pos);

            /**
             * Returns the current medium.
             * @return the current medium
             */
            Music *getMedium() const;

            /**
             * Removes all mediums from the playlist and loads new files from
             * the given path into the playlist.
             * @param path the path to the new playlist elements
             * @return the new playlist path
             */
            std::string setPlaylistPath(std::string path);

            /**
             * Returns the current playlist path
             * @return the new playlist path
             */
            std::string getPlaylistPath() const;
        };
    }
}

#endif //TURBO_MEDIA_PLAYER_H
