#include "audio/audio.h"

using namespace AUDIO;
using EXTERN::XML;

Chunk::Chunk(string file_path, bool is_xml)
	: file_path(file_path)
{
	if(is_xml)
    {
        if(EXTERN::Directory::isType(file_path, "xml"))
        {
            EXTERN::XMLParser parser(file_path);
            XML xml = parser.getXML();
            XML sp = xml.findTag("Chunk");
            if(!sp.isEmpty())
            {
                string rel_path = sp.getValue("relPath");
                if(rel_path != "")
                {
                    file_path = rel_path;
                }
            }
        }
    }
    this->file_path = file_path;

    if(EXTERN::Directory::hasFilter(file_path, "wav"))
    {
        this->chunk = Mix_LoadWAV(file_path.c_str());
		this->state = MEDIA_STATE::IDLE;
    }
}

Mix_Chunk * Chunk::getChunk()
{
	return this->chunk;
}

void Chunk::play(int loops, long time)
{
	if(this->state != MEDIA_STATE::PLAYING)
	{
		this->state = MEDIA_STATE::PLAYING;
		if(time == 0)
		{
			Mix_PlayChannel(TURBO::SDL_MIX_DEFAULT_CHANNEL, this->chunk, loops);
		}
		else
		{
			Mix_PlayChannelTimed(TURBO::SDL_MIX_DEFAULT_CHANNEL, this->chunk, loops, time);
		}
	}
}

void Chunk::stop()
{
	if(this->state != MEDIA_STATE::STOPPED)
	{
		this->state = MEDIA_STATE::STOPPED;
		Mix_HaltChannel(TURBO::SDL_MIX_DEFAULT_CHANNEL);
	}
}

Chunk::~Chunk()
{
	Mix_FreeChunk(this->chunk);
}

Music::Music(string file_path, bool is_xml)
	: file_path(file_path)
{
	if(is_xml)
    {
        if(EXTERN::Directory::isType(file_path, "xml"))
        {
            EXTERN::XMLParser parser(file_path);
            XML xml = parser.getXML();
            XML sp = xml.findTag("Music");
            if(!sp.isEmpty())
            {
                string rel_path = sp.getValue("relPath");
                if(rel_path != "")
                {
                    file_path = rel_path;
                }
            }
        }
    }
    this->file_path = file_path;

    if(EXTERN::Directory::hasFilter(file_path, TURBO::SDL_MIX_FILE_FILTER))
    {
        this->music = Mix_LoadMUS(file_path.c_str());
		this->state = MEDIA_STATE::IDLE;
    }
}

Mix_Music * Music::getMusic()
{
	return this->music;
}

void Music::play(int loops)
{
	if(this->state != MEDIA_STATE::PLAYING)
	{
		this->state = MEDIA_STATE::PLAYING;
		Mix_PlayMusic(this->music, loops);
	}
}

void Music::pause()
{
	if(this->state == MEDIA_STATE::PLAYING)
	{
		this->state = MEDIA_STATE::PAUSED;
		Mix_PauseMusic();
	}
}

void Music::resume()
{
	if(this->state == MEDIA_STATE::PAUSED)
	{
		this->state = MEDIA_STATE::PLAYING;
		Mix_ResumeMusic();
	}
}

void Music::stop()
{
	if(this->state != MEDIA_STATE::STOPPED)
	{
		this->state = MEDIA_STATE::STOPPED;
		Mix_HaltMusic();
	}
}

Music::~Music()
{
	Mix_FreeMusic(this->music);
}