/********************
** TURBO **
*********************
**
** This project ...
**
*********************/

#ifndef TURBO_PLATFORM_H_INCLUDED
#define TURBO_PLATFORM_H_INCLUDED

#ifndef TURBO_PLATFORM
	#if defined WIN32
		#if defined WIN64
			#define TURBO_PLATFORM "WINDOWS 64"
		#else
			#define TURBO_PLATFORM "WINDOWS 32"
		#endif
	#elif defined __APPLE__
		#define TURBO_PLATFORM "MAC OS"
	#elif defined __linux__
		#define TURBO_PLATFORM "LINUX"
	#elif defined __unix__
		#define TURBO_PLATFORM "UNIX"
	#else
		#define TURBO_PLATFORM "UNDEFINED"
	#endif
#endif

/// C Libraries

/// C++ Libraries
#include <algorithm>
#include <array>
#include <cmath>
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
#include "Python.h"


/// Third Party Libraries
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"

typedef unsigned char 		Uint8;
typedef signed char 		Sint8;
typedef unsigned short 		Uint16;
typedef signed short 		Sint16;
typedef unsigned int 		Uint32;
typedef signed int 			Sint32;
typedef unsigned long long 	Uint64;
typedef signed long long 	Sint64;

using std::cerr;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::left;
using std::right;
using std::setw;

using std::function;
using std::istringstream;
using std::string;

using std::array;
using std::list;
using std::map;
using std::pair;
using std::queue;
using std::vector;

using std::min;
using std::max;

namespace TURBO
{

}

#endif // TURBO_PLATFORM_H_INCLUDED
