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
	typedef float				Float;
	typedef double				Double;
}

#endif // TURBO_PLATFORM_H_INCLUDED
