#include "audio/media_player.h"

namespace TURBO
{
    namespace AUDIO
    {
        PLAYER_STATE MediaPlayer::getState() const
        {
            return state;
        }

        PLAYER_STATE MediaPlayer::play()
        {
            if(state == PLAYER_STATE::STOPPED)
            {
                state = PLAYER_STATE::PLAYING;
            }
            return state;
        }

        PLAYER_STATE MediaPlayer::pause()
        {
            if(state == PLAYER_STATE::PLAYING)
            {
                state = PLAYER_STATE::PAUSED;
            }
            return state;
        }

        PLAYER_STATE MediaPlayer::resume()
        {
            if(state == PLAYER_STATE::PAUSED)
            {
                state = PLAYER_STATE::PLAYING;
            }
            return state;
        }

        PLAYER_STATE MediaPlayer::stop()
        {
            if(state != PLAYER_STATE::STOPPED)
            {
                state = PLAYER_STATE::STOPPED;
            }
            return state;
        }

        std::vector<Music &> MediaPlayer::addToPlaylist(Music &music, int index)
        {
            if(index == -1)
            {
                playlist.push_back(music);
            }
            else
            {
                playlist.insert(playlist.begin() + index, music);
            }
            return playlist;
        }

        std::vector<Music &> MediaPlayer::removeFromPlaylist(Music &music)
        {
            playlist.erase(std::find(playlist.begin(), playlist.end(), music));
            return playlist;
        }

        std::vector<Music &> MediaPlayer::removeFromPlaylist(int index)
        {
            playlist.erase(playlist.begin() + index);
            return playlist;
        }

        std::vector<Music &> MediaPlayer::getPlaylist() const
        {
            return playlist;
        }

        Uint64 MediaPlayer::getPlaylistSize() const
        {
            return playlist.size();
        }

        Music &MediaPlayer::setMedium(Music &music)
        {
            current_medium = music;
            return current_medium;
        }

        Music &MediaPlayer::getMedium() const
        {
            return current_medium;
        }
    }
}