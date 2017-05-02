#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

/**
*** @module     EXTERN
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		:
***
***
**/

#include "Turbo_main.h"
#include "extern/time.h"
#include "utils/log.h"

namespace SYSTEM
{
    /**
	*** @class System
	***
	***
	**/
    class System
    {
	private:
		const std::string TAG = "System";

    public:
        static void run(std::string path, std::string prefix, std::string flags);
    };

    /**
	*** @class SDL
	***
	***
	**/
    class SDL
    {
	private:
		const std::string           TAG = "SDL";
        std::map<std::string, bool> initState = { {"SDL", false}, {"IMG", false}, {"TTF", false},
                                                  {"MIX", false}, {"NET", false}};
		EXTERN::Timer               timer;
		std::string                 base_path;
		std::string                 pref_path;
		std::string                 revision;
		std::string                 version;

		bool initSDL();
        bool quitSDL();
        bool initIMAGE();
        bool quitIMAGE();
        bool initTTF();
        bool quitTTF();
        bool initMIXER();
        bool quitMIXER();
        bool initNET();
        bool quitNET();

    public:
        SDL();
        static std::string getBasePath();
        static std::string createPrefPath(std::string dirname);
        static std::string getRevision();
        static std::string getVersion();
        bool init();
        bool quit();
        ~SDL();
    };

    /**
	*** @class Platform
	***
	***
	**/
    class Platform
    {
    private:
    	const std::string	TAG = "Platform";
    	std::string 		platform;

    	Uint16              audio_devices;
    	Uint16              audio_drivers;
    	Uint16              display_modes;
    	Uint16              video_displays;
    	Uint16              video_drivers;

    	Uint16              curr_audio_driver;
    	Uint16              curr_display_mode;
    	Uint16              curr_video_driver;

    	Uint8			    cpu;
		Uint8 			    cpu_logical;
		Uint8			    cpu_virtual;
		Uint32 			    ram;

    public:
    	Platform();
    	std::string 		getPlatform();
    	Uint16              getAudioDevices();
    	Uint16              getAudioDrivers();
    	Uint16              getDisplayModes();
    	Uint16              getVideoDisplays();
    	Uint16              getVideoDrivers();
    	Uint8 			    getCpuLogical();
    	Uint8 			    getCpuVirtual();
    	Uint32 			    getRamAbsolute();
    	~Platform();
    };
}

#endif // SYSTEM_H_INCLUDED
