#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/**
*** @module     UTILS
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		:
***
***
**/

#include "Turbo_main.h"

namespace UTILS
{
	/**
	*** @enum LOG_TYPE
	**/
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

#endif // UTILS_H_INCLUDED
