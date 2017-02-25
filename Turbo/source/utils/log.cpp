#include "utils/log.h"

using namespace UTILS;

using TURBO::LOG_TYPE;

void Log::log(string tag, string message, LOG_TYPE type)
{
	ofstream log(LOGFILE, std::ios_base::out | std::ios_base::app);
	log << Timer::getTimeString() << SPACE << LOG << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::info(string tag, string message, LOG_TYPE type)
{
	ofstream log(INFOFILE, std::ios_base::out | std::ios_base::app);
	log << Timer::getTimeString() << SPACE << LOG << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::warning(string tag, string message, LOG_TYPE type)
{
	ofstream war(WARFILE, std::ios_base::out | std::ios_base::app);
	war << Timer::getTimeString() << SPACE << WAR << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::error(string tag, string message, LOG_TYPE type)
{
	ofstream err(ERRFILE, std::ios_base::out | std::ios_base::app);
	err << Timer::getTimeString() << SPACE << ERR << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::debug(string tag, string message, LOG_TYPE type)
{
	ofstream deb(DEBFILE, std::ios_base::out | std::ios_base::app);
	deb << Timer::getTimeString() << SPACE << setw(20) << left << tag
		<< SPACE << message << endl;
}

void Log::console(string tag, string message, LOG_TYPE type)
{
	if(state >= LOG_TYPE::ERROR)
	{
		cout << Timer::getTimeString() << SPACE << setw(20) << left << tag
		     << SPACE << message << endl;
	}
}

void Log::clear(string filename)
{
	fstream file(filename, std::ios_base::trunc | std::ios_base::out);
}