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
		const std::string TAG = "SDL";

    private:
        std::map<std::string, bool> initState = { {"SDL", false}, {"IMG", false}, {"TTF", false},
                                                  {"MIX", false}, {"NET", false}};
		EXTERN::Timer               timer;

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
    	std::string 		name;
    	std::string 		version;
    	Uint8			    cpu;
		Uint8 			    cpuLogical;
		Uint8			    cpuVirtual;
		Uint32 			    ram;

    public:
    	Platform();
    	std::string 		getPlatform();
    	std::string 		getVersion();
    	Uint8 			    getCpuLogical();
    	Uint8 			    getCpuVirtual();
    	Uint32 			    getRamAbsolute();
    	~Platform();
    };
}

#endif // SYSTEM_H_INCLUDED
