#ifndef TURBO_CONSTANTS_H_INCLUDED
#define TURBO_CONSTANTS_H_INCLUDED

#include "Turbo_platform.h"

namespace TURBO
{
	/// Mathematical constants

	const static double PI = 3.141592653589793238462643383279502884197169399375105820974944;



	/// SDL constants

	const Uint32	    BORDERLESS				= SDL_WINDOW_BORDERLESS;
	const Uint32	    FULLSCREEN				= SDL_WINDOW_FULLSCREEN;

    const Uint32 	    SDL_INIT_FLAGS 			= SDL_INIT_EVERYTHING;
    const Uint32	    SDL_IMG_INIT_FLAGS 		= IMG_INIT_PNG;
    const Uint32 	    SDL_MIX_INIT_FLAGS 		= MIX_INIT_MOD; //| MIX_INIT_OGG
    const Uint32 	    SDL_WINDOW_FLAGS 		= SDL_WINDOW_SHOWN; // | SDL_WINDOW_BORDERLESS;
    const Uint32 	    SDL_RENDER_FLAGS 		= SDL_RENDERER_ACCELERATED;

    const std::string   SDL_IMG_FILE_FILTER     = "BMP,GIF,JPEG,LBM,PCX,PNG,PNM,TGA,TIFF,WEBP,XCF,XPM,XV";
    const Uint32 	    SDL_IMG_PIXEL_FORMAT	= SDL_PIXELFORMAT_RGBA8888;
    const Uint32	    SDL_IMG_TEXTURE_ACCESS	= SDL_TEXTUREACCESS_TARGET;

    const std::string   SDL_MIX_FILE_FILTER     = "WAV,VOC,MP3,OGG,FLAC,MIDI,IMF";
    const Uint32	    SDL_MIX_FREQUENCY		= 44100;
	const Sint32        SDL_MIX_FORMAT          = MIX_DEFAULT_FORMAT;
    const int           SDL_MIX_STEREO_CHANNEL  = 2;
    const int 		    SDL_MIX_DEFAULT_CHANNEL	= -1;
    const int           SDL_MIX_CHUNK_SIZE    	= 4096;
    const int           SDL_MIX_MAX_VOL       	= MIX_MAX_VOLUME;
    const int           SDL_MIX_MIN_VOL       	= 0;


    /// Turbo constants

    const Uint16        TURBO_FPS_LOCK          = 120;

    const std::string 	TURBO_PATH_SCRIPT       = "source/script/";

	const std::string 	TURBO_PATH_DATA			= "data/";
    const std::string 	TURBO_PATH_FONT			= "data/font/";
    const std::string 	TURBO_PATH_IMAGE		= "data/image/";
    const std::string 	TURBO_PATH_SPRITE		= "data/image/sprites/";
    const std::string 	TURBO_PATH_MUSIC        = "data/audio/music/";
    const std::string 	TURBO_PATH_SOUND        = "data/audio/sounds/";
    const std::string	TURBO_PATH_SAVES		= "data/save/";
    const std::string	TURBO_PATH_SCREENSHOT	= "data/screenshot/";
    const std::string 	TURBO_PATH_XML 			= "data/xml/";
    const std::string 	TURBO_PATH_XML_AUDIO 	= "data/xml/audio/";
    const std::string 	TURBO_PATH_XML_FONT 	= "data/xml/font/";
    const std::string	TURBO_PATH_XML_GAME		= "data/xml/game/";
    const std::string 	TURBO_PATH_XML_IMAGE 	= "data/xml/image/";
    const std::string 	TURBO_PATH_XML_LAYOUT	= "data/xml/layout/";
    const std::string 	TURBO_PATH_XML_MAP 		= "data/xml/map/";
    const std::string 	TURBO_PATH_XML_TEXT 	= "data/xml/text/";

    const std::string   TURBO_LOGFILE           = TURBO_PATH_DATA + "log.txt";
    const std::string   TURBO_WARFILE           = TURBO_PATH_DATA + "war.txt";
    const std::string   TURBO_ERRFILE           = TURBO_PATH_DATA + "err.txt";
    const std::string   TURBO_DEBFILE           = TURBO_PATH_DATA + "deb.txt";
    const std::string   TURBO_INFOFILE          = TURBO_PATH_DATA + "info.txt";
    const std::string   TURBO_SETTINGSFILE      = TURBO_PATH_DATA + "settings.ini";

    /// Other

    const SDL_Color     _TRANSPARENT	            = {0x00, 0x00, 0x00, 0x00};
    const SDL_Color     _BLACK			        = {0x00, 0x00, 0x00, 0xFF};
    const SDL_Color     _RED			            = {0xFF, 0x00, 0x00, 0xFF};
    const SDL_Color     _GREEN                   = {0x00, 0xFF, 0x00, 0xFF};
    const SDL_Color     _BLUE			        = {0x00, 0x00, 0xFF, 0xFF};
    const SDL_Color     _WHITE			        = {0xFF, 0xFF, 0xFF, 0xFF};
    const SDL_Color     _YELLOW		            = {0xFF, 0xFF, 0x00, 0xFF};
    const SDL_Color     _MAGENTA		            = {0xFF, 0x00, 0xFF, 0xFF};
    const SDL_Color     _CYAN			        = {0x00, 0xFF, 0xFF, 0xFF};

    const std::string   LOG                     = "[LOG]";
    const std::string   WAR                     = "[WARNING]";
    const std::string   ERR                     = "[ERROR]";
    const std::string   DEBUG                   = "[DEBUG]";
    const std::string   INFO                    = "[INFO]";
    const std::string   SPACE                   = " ";
}

#endif // TURBO_CONSTANTS_H_INCLUDED
