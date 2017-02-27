#ifndef TURBO_CONSTANTS_H_INCLUDED
#define TURBO_CONSTANTS_H_INCLUDED

#include "Turbo_platform.h"

namespace TURBO
{
	/// Mathematical constants

	const static double PI = 3.141592653589793238462643383279502884197169399375105820974944;



	/// SDL constants

	const Uint32	BORDERLESS				    = SDL_WINDOW_BORDERLESS;
	const Uint32	FULLSCREEN				    = SDL_WINDOW_FULLSCREEN;

    const Uint32 	SDL_INIT_FLAGS 			    = SDL_INIT_EVERYTHING;
    const Uint32	SDL_IMG_INIT_FLAGS 		    = IMG_INIT_PNG;
    const Uint32 	SDL_MIX_INIT_FLAGS 		    = MIX_INIT_MOD; //| MIX_INIT_OGG
    const Uint32 	SDL_WINDOW_FLAGS 		    = SDL_WINDOW_SHOWN; // | SDL_WINDOW_BORDERLESS;
    const Uint32 	SDL_RENDER_FLAGS 		    = SDL_RENDERER_ACCELERATED;

    const Uint32 	SDL_IMG_PIXEL_FORMAT	    = SDL_PIXELFORMAT_RGBA8888;
    const Uint32	SDL_IMG_TEXTURE_ACCESS	    = SDL_TEXTUREACCESS_TARGET;

    const Uint32	SDL_MIX_FREQUENCY		    = 44100;
	const Sint32    SDL_MIX_FORMAT              = MIX_DEFAULT_FORMAT;
    const int       SDL_MIX_STEREO_CHANNEL      = 2;
    const int 		SDL_MIX_DEFAULT_CHANNEL	    = -1;
    const int       SDL_MIX_CHUNK_SIZE    	    = 4096;
    const int       SDL_MIX_MAX_VOL       	    = MIX_MAX_VOLUME;
    const int       SDL_MIX_MIN_VOL       	    = 0;


    /// Turbo constants

    const std::string 	TURBO_PATH_SCRIPT       = "src/script/";

	const std::string 	TURBO_PATH_DATA			= "data/";
    const std::string 	TURBO_PATH_FONT			= "data/font/";
    const std::string 	TURBO_PATH_IMAGE		= "data/img/";
    const std::string 	TURBO_PATH_SPRITE		= "data/img/sprites/";
    const std::string 	TURBO_PATH_GAME 		= "data/game/";
    const std::string 	TURBO_PATH_LAYOUT		= "data/layout/";
    const std::string 	TURBO_PATH_MAP 			= "data/map/";
    const std::string 	TURBO_PATH_MUSIC        = "data/sound/music/";
    const std::string 	TURBO_PATH_SOUND        = "data/sound/sounds/";
    const std::string 	TURBO_PATH_TEXT         = "data/text/";
    const std::string	TURBO_PATH_SAVES		= "data/saves/";
    const std::string	TURBO_PATH_SCREENSHOT	= "data/screenshots/";
    const std::string 	TURBO_PATH_XML 			= "data/xml/";
    const std::string 	TURBO_PATH_XML_FONT 	= "data/xml/font/";
    const std::string 	TURBO_PATH_XML_IMAGE 	= "data/xml/img/";
    const std::string	TURBO_PATH_XML_GAME		= "data/xml/game/";
    const std::string 	TURBO_PATH_XML_LAYOUT	= "data/xml/layout/";
    const std::string 	TURBO_PATH_XML_MAP 		= "data/xml/map/";
    const std::string 	TURBO_PATH_XML_SOUND 	= "data/xml/sound/";
    const std::string 	TURBO_PATH_XML_TEXT 	= "data/xml/text/";

    const std::string   TURBO_LOGFILE           = TURBO_PATH_DATA + "log.txt";
    const std::string   TURBO_WARFILE           = TURBO_PATH_DATA + "war.txt";
    const std::string   TURBO_ERRFILE           = TURBO_PATH_DATA + "err.txt";
    const std::string   TURBO_DEBFILE           = TURBO_PATH_DATA + "deb.txt";
    const std::string   TURBO_INFOFILE          = TURBO_PATH_DATA + "info.txt";

    /// Other

    const SDL_Color     TRANSPARENT	            = {0x00, 0x00, 0x00, 0x00};
    const SDL_Color     BLACK			        = {0x00, 0x00, 0x00, 0xFF};
    const SDL_Color     RED			            = {0xFF, 0x00, 0x00, 0xFF};
    const SDL_Color     GREEN                   = {0x00, 0xFF, 0x00, 0xFF};
    const SDL_Color     BLUE			        = {0x00, 0x00, 0xFF, 0xFF};
    const SDL_Color     WHITE			        = {0xFF, 0xFF, 0xFF, 0xFF};
    const SDL_Color     YELLOW		            = {0xFF, 0xFF, 0x00, 0xFF};
    const SDL_Color     MAGENTA		            = {0xFF, 0x00, 0xFF, 0xFF};
    const SDL_Color     CYAN			        = {0x00, 0xFF, 0xFF, 0xFF};

    const std::string   LOG                     = "[LOG]";
    const std::string   WAR                     = "[WARNING]";
    const std::string   ERR                     = "[ERROR]";
    const std::string   DEBUG                   = "[DEBUG]";
    const std::string   INFO                    = "[INFO]";
    const std::string   SPACE                   = " ";
}


#endif // TURBO_CONSTANTS_H_INCLUDED
