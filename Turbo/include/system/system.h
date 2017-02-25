#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

namespace SYSTEM
{
    /**
	*** @class System
	***
	***
	**/
    class System
    {
    public:
        static void run(string path, string prefix, string flags);
    };

    /**
	*** @class SDL
	***
	***
	**/
    class SDL
    {
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
    	string 			name;
    	string 			version;
    	int				cpu;
		int 			cpuLogical;
		int				cpuVirtual;
		int 			ram;

    public:
    	Platform();
    	string 			getPlatform();
    	string 			getVersion();
    	int 			getCpuLogical();
    	int 			getCpuVirtual();
    	int 			getRamAbsolute();
    	~Platform();
    };
}

#endif // SYSTEM_H_INCLUDED
