#ifndef TURBO_H_INCLUDED
#define TURBO_H_INCLUDED

#include <fstream>
#include <functional>
#include <iostram>

#include "SDL.h"

#include "Turbo_constants.h"

namespace TURBO
{
	enum class FILE_STATE
	{
		CLOSED = 0,
		OPEN = 1
	};
}


#endif // TURBO_H_INCLUDED
