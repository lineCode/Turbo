#include "utils/log.h"

using namespace UTILS;

using namespace TURBO;
using EXTERN::Timer;

void Log::log(string tag, string message, LOG_TYPE type)
{
	ofstream log(TURBO_LOGFILE, std::ios_base::out | std::ios_base::app);
	log << Timer::getTimeToString() << SPACE << LOG << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::info(string tag, string message, LOG_TYPE type)
{
	ofstream log(TURBO_INFOFILE, std::ios_base::out | std::ios_base::app);
	log << Timer::getTimeToString() << SPACE << LOG << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::warning(string tag, string message, LOG_TYPE type)
{
	ofstream war(TURBO_WARFILE, std::ios_base::out | std::ios_base::app);
	war << Timer::getTimeToString() << SPACE << WAR << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::error(string tag, string message, LOG_TYPE type)
{
	ofstream err(TURBO_ERRFILE, std::ios_base::out | std::ios_base::app);
	err << Timer::getTimeToString() << SPACE << ERR << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::debug(string tag, string message, LOG_TYPE type)
{
	ofstream deb(TURBO_DEBFILE, std::ios_base::out | std::ios_base::app);
	deb << Timer::getTimeToString() << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::console(string tag, string message, LOG_TYPE type)
{
	if(type >= LOG_TYPE::ERROR)
	{
		cout << Timer::getTimeToString() << SPACE << setw(20) << left << tag
			 << SPACE << message << endl;
	}
}

void Log::clear(string filename)
{
	fstream file(filename, std::ios_base::trunc | std::ios_base::out);
}