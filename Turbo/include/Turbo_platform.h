#ifndef TURBO_PLATFORM_H_INCLUDED
#define TURBO_PLATFORM_H_INCLUDED

#if defined WIN32 || defined __WIN32__ || defined WINDOWS || defined _WIN32 || defined __MINGW32__
	#define PLATFORM "WINDOWS"
#elifdef __APPLE__
	#define PLATFORM "MAC OS"
#elifdef __linux__
	#define PLATFORM "LINUX
#else
	#define PLATFORM "UNDEFINED"

/// C Libraries

/// C++ Libraries
#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <chrono>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>

/// Scripting Libraries
//#include "script/Python.h"

/// Third Party Libraries
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"

namespace TURBO
{
	typedef unsigned char 		Uint8;
	typedef signed char 		Sint8;
	typedef unsigned short 		Uint16;
	typedef signed short 		Sint16;
	typedef unsigned int 		Uint32;
	typedef signed int 			Sint32;
	typedef unsigned long long 	Uint64;
	typedef signed long long 	Sint64;

	enum class LOG_TYPE : Uint8
	{
		NOTHING = 0,
		VERBOSE = 1,
		ERROR 	= 2,
		WARNING = 3,
		LOG		= 4,
		CONSOLE = 5,
		DEBUG	= 6,
		RELEASE = 7
	};
}

#endif // TURBO_PLATFORM_H_INCLUDED
