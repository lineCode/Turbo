#include "turbo/application.h"

using namespace TURBO;
using UTILS::Log;

Application::Application()
    : sdl()
{
    Log::clear(TURBO_LOGFILE);
	Log::clear(TURBO_WARFILE);
	Log::clear(TURBO_ERRFILE);
	Log::clear(TURBO_DEBFILE);
	Log::clear(TURBO_INFOFILE);
}

unsigned int Application::run()
{
    return 0;
}

Application::~Application()
{

}