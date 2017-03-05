#include "system/system.h"

using namespace TURBO;
using namespace SYSTEM;

using UTILS::Log;
using UTILS::LOG_TYPE;

void System::run(string file, string prefix, string flags)
{
    string command = prefix + " " + file + " " + flags;
    system(command.c_str());
}


SDL::SDL() : timer()
{
    Log::clear(TURBO_LOGFILE);
	Log::clear(TURBO_WARFILE);
	Log::clear(TURBO_ERRFILE);
	Log::clear(TURBO_DEBFILE);
	Log::clear(TURBO_INFOFILE);
    this->init();
}

bool SDL::initSDL()
{
    bool success = false;

    if(SDL_Init(SDL_INIT_FLAGS) == 0)
    {
        this->initState["SDL"] = true;
        success = true;
        Log::log(this->TAG, "Init SDL", LOG_TYPE::LOG);
    }
    else
    {
		Log::error(this->TAG, ("Error at initSDL(): " + (string)SDL_GetError()), LOG_TYPE::ERROR);
    }
    return success;
}

bool SDL::quitSDL()
{
    bool success = false;

	if(this->initState["SDL"])
	{
		SDL_Quit();
		this->initState["SDL"] = false;
		success = true;
		Log::log(this->TAG, "Quit SDL", LOG_TYPE::LOG);
	}
	else
	{
		Log::error(this->TAG, ("Error at quitSDL(): " + (string)SDL_GetError()), LOG_TYPE::ERROR);
	}
    return success;
}

bool SDL::initIMAGE()
{
    bool success = false;

    if(this->initState["SDL"] == true)
    {
        if(IMG_Init(SDL_IMG_INIT_FLAGS))
        {
            this->initState["IMG"] = true;
            success = true;
            Log::log(this->TAG, "Init SDL_IMG", LOG_TYPE::LOG);
        }
        else
        {
			Log::error(this->TAG, ("Error at InitIMAGE(): " + (string)IMG_GetError()), LOG_TYPE::ERROR);
        }
    }
    return success;
}

bool SDL::quitIMAGE()
{
    bool success = false;

	if(this->initState["IMG"])
	{
		IMG_Quit();
		this->initState["IMG"] = false;
		success = true;
		Log::log(this->TAG, "Quit SDL_IMG", LOG_TYPE::LOG);
	}
	else
	{
		Log::error(this->TAG, ("Error at quitIMAGE(): " + (string)IMG_GetError()), LOG_TYPE::ERROR);
	}
    return success;
}

bool SDL::initTTF()
{
    bool success = false;

    if(this->initState["SDL"] == true)
    {
        if(TTF_Init() == 0)
        {
            this->initState["TTF"] = true;
            success = true;
            Log::log(this->TAG, "Init SDL_TTF", LOG_TYPE::LOG);
        }
        else
        {
			Log::error(this->TAG, ("Error at initTTF(): " + (string)TTF_GetError()), LOG_TYPE::ERROR);
        }
    }
    return success;
}

bool SDL::quitTTF()
{
    bool success = false;

	if(this->initState["TTF"])
	{
		TTF_Quit();
		this->initState["TTF"] = false;
		success = true;
		Log::log(this->TAG, "Quit SDL_TTF", LOG_TYPE::LOG);
	}
	else
	{
		Log::error(this->TAG, ("Error at quitTTF(): " + (string)TTF_GetError()), LOG_TYPE::LOG);
	}
    return success;
}

bool SDL::initMIXER()
{
    bool success = false;

    if(this->initState["SDL"] == true)
    {
        if(Mix_Init(SDL_MIX_INIT_FLAGS) == 0)
        {
        	if(Mix_OpenAudio(SDL_MIX_FREQUENCY, SDL_MIX_FORMAT,
							 SDL_MIX_STEREO_CHANNEL, SDL_MIX_CHUNK_SIZE) == 0)
			{
				this->initState["MIX"] = true;
				success = true;
				Log::log(this->TAG, "Init SDL_MIX", LOG_TYPE::LOG);
			}
        }
        else
        {
			Log::error(this->TAG, ("Error at initMIXER(): " + (string)Mix_GetError()), LOG_TYPE::ERROR);
        }
    }
    return success;
}

bool SDL::quitMIXER()
{
    bool success = false;

	if(this->initState["MIX"])
	{
		Mix_Quit();
		this->initState["MIX"] = false;
		success = true;
		Log::log(this->TAG, "Quit SDL_MIX", LOG_TYPE::LOG);
	}
	else
	{
		Log::error(this->TAG, ("Error at SDL_MIX(): " + (string)Mix_GetError()), LOG_TYPE::ERROR);
	}

    return success;
}

bool SDL::initNET()
{
    bool success = false;

    if(this->initState["SDL"] == true)
    {
        if(SDLNet_Init() == 0)
        {
            this->initState["NET"] = true;
            success = true;
            Log::log(this->TAG, "Init SDL_NET", LOG_TYPE::LOG);
        }
        else
        {
			Log::error(this->TAG, ("Error at initNET(): " + (string)SDLNet_GetError()), LOG_TYPE::ERROR);
        }
    }
    return success;
}

bool SDL::quitNET()
{
    bool success = false;

	if(this->initState["NET"])
	{
		SDLNet_Quit();
		this->initState["NET"] = false;
		success = true;
		Log::log(this->TAG, "Quit SDL_NET", LOG_TYPE::LOG);
	}
	else
	{
		Log::error(this->TAG, ("Error at quitNET(): " + (string)SDLNet_GetError()), LOG_TYPE::LOG);
	}

    return success;
}

bool SDL::init()
{
	bool success = false;

	if(this->initSDL())
	{
		if(this->initIMAGE() && this->initTTF() && this->initMIXER() && this->initNET())
		{
			success = true;
		}
	}

	return success;
}

bool SDL::quit()
{
	bool success = false;

	this->quitNET();
    this->quitMIXER();
    this->quitTTF();
    this->quitIMAGE();
    this->quitSDL();

	return success;
}

SDL::~SDL()
{
	this->quit();
	this->timer.stop();
}

Platform::Platform()
{
	this->name = SDL_GetPlatform();
	this->cpu = SDL_GetCPUCount();
	this->ram = SDL_GetSystemRAM();
}

string Platform::getPlatform()
{
	return this->name;
}

Uint8 Platform::getCpuLogical()
{
	return this->cpuLogical;
}

Uint8 Platform::getCpuVirtual()
{
    return this->cpuVirtual;
}

Uint32 Platform::getRamAbsolute()
{
    return this->ram;
}

Platform::~Platform()
{

}