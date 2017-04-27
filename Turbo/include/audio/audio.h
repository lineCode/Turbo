#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

/**
*** @module     audio
*** @author 	Christoph Zorn
*** @date       24.02.2017
***
*** @brief      The module audio contains
***
***
**/

#include "Turbo_main.h"
#include "extern/parser.h"
#include "extern/directory.h"

namespace AUDIO
{
    /**
    *** @enum MEDIA_STATE
    **/
    enum class MEDIA_STATE : Uint8
    {
        STOPPED	= 0,
        IDLE	= 1,
        PLAYING	= 2,
        PAUSED	= 3
    };

    /**
    *** @class  Chunk
    ***
    *** @var
    **/
	class Chunk
	{
	private:
		const std::string   TAG = "Chunk";
		Mix_Chunk         * chunk;

	protected:
		std::string         file_path;
		MEDIA_STATE			state = MEDIA_STATE::STOPPED;

	public:
		Chunk(std::string file_path, bool is_xml = true);
		Mix_Chunk         * getChunk();
		void                play(int loops = 0, long time = 0);
		void                stop();
		~Chunk();
	};

	/**
	*** @class  Music
	***
	*** @var
	**/
	class Music
	{
	private:
		const std::string   TAG = "Music";
		Mix_Music 		  * music;

	protected:
		std::string         file_path;
		MEDIA_STATE			state = MEDIA_STATE::STOPPED;

	public:
		Music(std::string file_path, bool is_xml = true);
		Mix_Music         * getMusic();
		void                play(int loops = 0);
		void                pause();
		void                resume();
		void                stop();
		~Music();
	};
}

#endif // AUDIO_H_INCLUDED
