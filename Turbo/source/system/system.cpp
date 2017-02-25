#include "system/system.h"

using namespace SYSTEM;

void System::run(string file, string prefix, string flags)
{
    string command = prefix + " " + file + " " + flags;
    system(command.c_str());
}


SDL::SDL() : timer()
{
	Log::clear(LOGFILE);
	Log::clear(ERRFILE);
	Log::clear(WARFILE);
    this->init();
}

bool SDL::initSDL()
{
    bool success = false;

    if(SDL_Init(SDL_INIT_FLAGS) == 0)
    {
        this->initState["SDL"] = true;
        success = true;
        Log::log(this->TAG, LOG_00_00, log_state::log);
    }
    else
    {
		Log::error(this->TAG, ERR_00_00 + TAB + SDL_GetError(), log_state::error);
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
		Log::log(this->TAG, LOG_00_01, log_state::log);
	}
	else
	{
		Log::error(this->TAG, ERR_00_01 + TAB + SDL_GetError(), log_state::error);
	}

    return success;
}

bool SDL::initIMAGE()
{
    bool success = false;

    if(this->initState["SDL"] == true)
    {
        if(IMG_Init(IMG_INIT_FLAGS))
        {
            this->initState["IMG"] = true;
            success = true;
            Log::log(this->TAG, LOG_01_00, log_state::log);
        }
        else
        {
			Log::error(this->TAG, ERR_01_00 + TAB + IMG_GetError(), log_state::error);
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
		Log::log(this->TAG, LOG_01_01, log_state::log);
	}
	else
	{
		Log::error(this->TAG, ERR_01_01 + TAB + IMG_GetError(), log_state::error);
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
            Log::log(this->TAG, LOG_02_00, log_state::log);
        }
        else
        {
			Log::error(this->TAG, ERR_02_00 + TAB + TTF_GetError(), log_state::error);
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
		Log::log(this->TAG, LOG_02_01, log_state::log);
	}
	else
	{
		Log::error(this->TAG, ERR_02_01 + TAB + TTF_GetError(), log_state::error);
	}

    return success;
}

bool SDL::initMIXER()
{
    bool success = false;

    if(this->initState["SDL"] == true)
    {
        if(Mix_Init(MIX_INIT_FLAGS) == 0)
        {
        	if(Mix_OpenAudio(GAME::SOUND_FREQUENCY, GAME::SOUND_FORMAT,
							 GAME::SOUND_STEREO_CHANNEL, GAME::SOUND_CHUNK_SIZE) == 0)
			{
				this->initState["MIX"] = true;
				success = true;
				Log::log(this->TAG, LOG_03_00, log_state::log);
			}
        }
        else
        {
			Log::error(this->TAG, ERR_03_00 + TAB + Mix_GetError(), log_state::error);
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
		Log::log(this->TAG, LOG_03_01, log_state::log);
	}
	else
	{
		Log::error(this->TAG, ERR_03_01 + TAB + Mix_GetError(), log_state::error);
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
            Log::log(this->TAG, LOG_04_00, log_state::log);
        }
        else
        {
			Log::error(this->TAG, ERR_04_00 + TAB + SDLNet_GetError(), log_state::error);
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
		Log::log(this->TAG, LOG_04_01, log_state::log);
	}
	else
	{
		Log::error(this->TAG, ERR_04_01 + TAB + SDLNet_GetError(), log_state::error);
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

int Platform::getCpuLogical()
{
	return this->cpu;
}

int Platform::getRamAbsolute()
{
    return this->ram;
}

Platform::~Platform()
{

}