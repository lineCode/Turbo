#include "audio/media_player.h"

namespace TURBO
{
    namespace AUDIO
    {
        MediaPlayer::MediaPlayer(const std::string path)
            : position(),
              path(path)
        {
            position.reset();
            UTIL::Dir dir(path);
            for(auto file : dir.getFiles())
            {
                if(UTIL::File::hasFilter(file, std::vector<std::string>{"MP3", "FLAC"}))
                {
                    Music * m = new Music(file);
                    playlist.push_back(m);
                    current_medium = m;
                }
            }
        }

        MediaPlayer::~MediaPlayer()
        {
            for(auto file : playlist)
            {
                file->~Music();
            }
        }

        void MediaPlayer::finished()
        {
            // TODO callback
        }

        MEDIUM_STATE MediaPlayer::getState() const
        {
            return current_medium->getState();
        }

        void MediaPlayer::onFinish(void * callback)
        {
            //TODO set callback
        }

        void MediaPlayer::onMediaChanged(void *callback)
        {

        }

        void MediaPlayer::onPositionChanged(void *callback)
        {

        }

        void MediaPlayer::onStateChanged(void *callback)
        {

        }

        void MediaPlayer::onVolumeChanged(void *callback)
        {

        }

        bool MediaPlayer::playing()
        {
            return Mix_PlayingMusic() == 1;
        }

        bool MediaPlayer::paused()
        {
            return Mix_PausedMusic() == 1;
        }

        Uint8 MediaPlayer::setVolume(Uint8 volume)
        {
            if(volume >= MIN_VOLUME && volume <= MAX_VOLUME)
            {
                this->volume = volume;
                if(Mix_VolumeMusic(volume) < 0)
                {
                    return 0;
                }
            }
            return this->volume;
        }

        Uint8 MediaPlayer::getVolume() const
        {
            return this->volume;
        }

        Uint32 MediaPlayer::getPosition()
        {
            return position.getActiveTime();
        }

        Uint32 MediaPlayer::setPosition(Uint32 position)
        {
            double new_position = position / 1000;
            if(Mix_SetMusicPosition(new_position) == 0)
            {
                this->position.addActiveTime(position - this->position.getActiveTime());
                return this->position.getActiveTime();
            }
            else
            {
                return 0;
            }
        }

        MEDIUM_STATE MediaPlayer::rewind()
        {
            if(current_medium->rewind() == MEDIUM_STATE::STOPPED)
            {
                position.reset();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::play()
        {
            if(current_medium->play() == MEDIUM_STATE::PLAYING)
            {
                position.start();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::pause()
        {
            if(current_medium->pause() == MEDIUM_STATE::PAUSED)
            {
                position.pause();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::resume()
        {
            if(current_medium->resume() == MEDIUM_STATE::PLAYING)
            {
                position.resume();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::stop()
        {
            if(current_medium->stop() == MEDIUM_STATE ::STOPPED)
            {
                position.stop();
            }
            return current_medium->getState();
        }

        std::vector<Music *> MediaPlayer::addToPlaylist(Music *music, int index)
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

        std::vector<Music *> MediaPlayer::removeFromPlaylist(Music *music)
        {
            auto pos = playlist.end();
            if((pos = std::find(playlist.begin(), playlist.end(), current_medium)) != playlist.end())
            {
                stop();
            }
            playlist.erase(pos);
            return playlist;
        }

        std::vector<Music *> MediaPlayer::removeFromPlaylist(int index)
        {
            if(std::find(playlist.begin(), playlist.end(), current_medium) == playlist.begin() + index)
            {
                stop();
            }
            playlist.erase(playlist.begin() + index);
            return playlist;
        }

        std::vector<Music *> MediaPlayer::getPlaylist() const
        {
            return playlist;
        }

        Uint64 MediaPlayer::getPlaylistSize() const
        {
            return playlist.size();
        }

        Music *MediaPlayer::setMedium(Music *music)
        {
            current_medium->stop();
            current_medium = music;
            return current_medium;
        }

        Music *MediaPlayer::getMedium() const
        {
            return current_medium;
        }

        std::string MediaPlayer::setPlaylistLocation(const std::string path)
        {
            this->path = path;
            return this->path;
        }

        std::string MediaPlayer::getPlaylistLocation() const
        {
            return this->path;
        }
    }
}