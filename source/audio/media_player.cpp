#include "audio/media_player.h"

namespace TURBO
{
    namespace AUDIO
    {
        MediaPlayer::MediaPlayer(const std::string path)
            : position(),
              path(path),
              playlist_position(0),
              volume(64),
              last_mute_volume(64),
              shuffle_on(false),
              repeat_on(false)
        {
            this->path = (path.back() == '/') ? path : path + "/";
            position.reset();
            UTIL::Dir dir(this->path);
            for(const auto &file : dir.getFiles())
            {
                if(UTIL::File::hasFilter(file, MUSIC_EXTENSIONS))
                {
                    Music *m = new Music(file);
                    playlist.push_back(m);
                    current_medium = m;
                }
            }
            setVolume(volume);
            setShuffle(shuffle_on);
            setRepeat(repeat_on);
        }

        MediaPlayer::~MediaPlayer()
        {
            stop();
            for(auto & file : playlist)
            {
                delete file;
            }
        }

        void MediaPlayer::fireCallback(Uint8 event)
        {
            if(callbacks.count(event) > 0)
            {
                callbacks[event]();
            }
        }

        MEDIUM_STATE MediaPlayer::getState() const
        {
            return current_medium->getState();
        }

        void MediaPlayer::registerCallback(Uint8 event, const std::function<void()> callback)
        {
            callbacks[event] = callback;
        }

        bool MediaPlayer::isPlaying()
        {
            return (Mix_PlayingMusic() == 1);
        }

        bool MediaPlayer::isPaused()
        {
            return (Mix_PausedMusic() == 1);
        }

        Uint8 MediaPlayer::setVolume(Uint8 volume)
        {
            if(volume >= MIN_VOLUME && volume <= MAX_VOLUME)
            {
                this->volume = volume;
                fireCallback(EVENT_TYPE::ON_VOLUME_CHANGED);
                if(Mix_VolumeMusic(volume) < 0)
                {
                    setMute(true);
                    return 0;
                }
            }
            return this->volume;
        }

        Uint8 MediaPlayer::getVolume() const
        {
            return this->volume;
        }

        Uint8 MediaPlayer::setMute(bool mute)
        {
            if(mute)
            {
                fireCallback(EVENT_TYPE::ON_MUTE);
                last_mute_volume = volume;
                volume           = 0;
            }
            else
            {
                fireCallback(EVENT_TYPE::ON_UNMUTE);
                volume = last_mute_volume;
            }
            return volume;
        }

        bool MediaPlayer::isMuted() const
        {
            return (volume > 0);
        }

        Uint32 MediaPlayer::getPosition()
        {
            return position.getActiveTime();
        }

        Uint32 MediaPlayer::setPosition(Uint32 position)
        {
            if(UTIL::File::hasFilter(current_medium->getPath(), std::vector<std::string>{"mp3", "ogg", "mod"}))
            {
                if(position > 0)
                {
                    double new_position = position / 1000;
                    if(Mix_SetMusicPosition(new_position) == 0)
                    {
                        fireCallback(EVENT_TYPE::ON_POSITION_CHANGED);
                        this->position.addActiveTime(position - this->position.getActiveTime());
                        return this->position.getActiveTime();
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }

        MEDIUM_STATE MediaPlayer::rewind()
        {
            if(current_medium->rewind() == MEDIUM_STATE::STOPPED)
            {
                position.reset();
                fireCallback(EVENT_TYPE::ON_REWIND);
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::setPlayback(bool play)
        {
            if(play)
            {
                LOG("play");
                current_medium->resume();
            }
            else
            {
                LOG("pause");
                current_medium->pause();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::togglePlayback()
        {
            if(current_medium->getState() == MEDIUM_STATE::PLAYING)
            {
                current_medium->pause();
            }
            else if(current_medium->getState() == MEDIUM_STATE::PAUSED)
            {
                current_medium->resume();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::play()
        {
            if(current_medium->play() == MEDIUM_STATE::PLAYING && current_medium != nullptr)
            {
                fireCallback(EVENT_TYPE::ON_PLAY);
                position.start();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::pause()
        {
            if(current_medium->pause() == MEDIUM_STATE::PAUSED && current_medium != nullptr)
            {
                fireCallback(EVENT_TYPE::ON_PAUSE);
                position.pause();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::resume()
        {
            if(current_medium->resume() == MEDIUM_STATE::PLAYING && current_medium != nullptr)
            {
                fireCallback(EVENT_TYPE::ON_RESUME);
                position.resume();
            }
            return current_medium->getState();
        }

        MEDIUM_STATE MediaPlayer::stop()
        {
            if(current_medium->stop() == MEDIUM_STATE::STOPPED && current_medium != nullptr)
            {
                fireCallback(EVENT_TYPE::ON_STOP);
                position.stop();
            }
            return current_medium->getState();
        }

        Music *MediaPlayer::next()
        {
            if(playlist_position == playlist.size() - 1)
            {
                setPlaylistPosition(0);
            }
            else
            {
                setPlaylistPosition(playlist_position + 1);
            }
            return current_medium;
        }

        Music *MediaPlayer::previous()
        {
            if(playlist_position == 0)
            {
                setPlaylistPosition(playlist.size() - 1);
            }
            else
            {
                setPlaylistPosition(playlist_position - 1);
            }
            return current_medium;
        }

        bool MediaPlayer::setShuffle(bool shuffle)
        {
            shuffle_on = shuffle;
            return shuffle_on;
        }

        bool MediaPlayer::getShuffle()
        {
            return shuffle_on;
        }

        bool MediaPlayer::setRepeat(bool repeat)
        {
            repeat_on = repeat;
            return repeat_on;
        }

        bool MediaPlayer::getRepeat()
        {
            return false;
        }

        std::vector<Music *> MediaPlayer::addToPlaylist(Music *music, int index)
        {
            if(music != nullptr)
            {
                fireCallback(EVENT_TYPE::ON_PLAYLIST_CHANGED);
                if(index == -1)
                {
                    playlist.push_back(music);
                }
                else
                {
                    playlist.insert(playlist.begin() + index, music);
                }
            }
            return playlist;
        }

        std::vector<Music *> MediaPlayer::removeFromPlaylist(Music *music)
        {
            auto pos = playlist.end();
            if((pos = std::find(playlist.begin(), playlist.end(), current_medium)) != playlist.end())
            {
                fireCallback(EVENT_TYPE::ON_PLAYLIST_CHANGED);
                stop();
            }
            playlist.erase(pos);
            return playlist;
        }

        std::vector<Music *> MediaPlayer::removeFromPlaylist(int index)
        {
            if(std::find(playlist.begin(), playlist.end(), current_medium) == playlist.begin() + index)
            {
                fireCallback(EVENT_TYPE::ON_PLAYLIST_CHANGED);
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

        Uint64 MediaPlayer::getPlaylistPosition() const
        {
            return playlist_position;
        }

        Uint64 MediaPlayer::setPlaylistPosition(Uint64 pos)
        {
            if(pos < playlist.size())
            {
                stop();
                Music *temp = current_medium;
                current_medium = *(playlist.begin() + pos);
                if(current_medium != nullptr)
                {
                    if(temp != current_medium)
                    {
                        fireCallback(EVENT_TYPE::ON_MEDIUM_CHANGED);
                    }
                    playlist_position = pos;
                    play();
                }
            }
            return playlist_position;
        }

        Music *MediaPlayer::getMedium() const
        {
            return current_medium;
        }

        std::string MediaPlayer::setPlaylistPath(const std::string path)
        {
            for(auto file : playlist)
            {
                delete file;
            }

            this->path = path;
            UTIL::Dir dir(path);

            for(const auto &file : dir.getFiles())
            {
                if(UTIL::File::hasFilter(file, MUSIC_EXTENSIONS))
                {
                    Music *m = new Music(file);
                    playlist.push_back(m);
                    current_medium = m;
                }
            }

            return this->path;
        }

        std::string MediaPlayer::getPlaylistPath() const
        {
            return this->path;
        }
    }
}