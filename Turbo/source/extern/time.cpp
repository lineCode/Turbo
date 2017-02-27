#include "extern/time.h"

using namespace EXTERN;

Timer::Timer()
{
	this->start();
}

Uint64 Timer::getTicks()
{
	return SDL_GetTicks();
}

Uint64 Timer::start()
{
	if(this->timer_state != TIMER_STATE::STARTED)
	{
		this->timer_value = 0;
		this->ival_start = this->getTicks();
		this->timer_state = TIMER_STATE::STARTED;
	}
	return this->ival_start;
}

Uint64 Timer::pause()
{
	if(this->timer_state == TIMER_STATE::STARTED)
	{
		this->ival_stop = this->getTicks();
		this->timer_state = TIMER_STATE::PAUSED;
		this->timer_value += (this->ival_stop - this->ival_start);
	}
	return this->ival_stop;
}

Uint64 Timer::resume()
{
	if(this->timer_state == TIMER_STATE::PAUSED)
	{
		this->ival_start = this->getTicks();
		this->timer_state = TIMER_STATE::STARTED;
	}
	return this->ival_start;
}

Uint64 Timer::stop()
{
	if(this->timer_state != TIMER_STATE::IDLE && this->timer_state != TIMER_STATE::STOPPED)
	{
		this->ival_stop = this->getTicks();
		this->timer_state = TIMER_STATE::STOPPED;
		this->timer_value += (this->ival_stop - this->ival_start);
	}
	return this->timer_value;
}

Uint64 Timer::getTime()
{
	this->pause();
	this->resume();
	return this->timer_value;
}

void Timer::sleep(Uint32 milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

string Timer::getTimeToString(Uint64 timestamp, string format)
{
	//time_t ti = time(&timestamp);
	//struct tm * time_info;
	//char buffer[100];
	//time_info = localtime(&ti);
	//string time_stringStrf = (string)strftime(buffer, format.c_str(), &time_info);

	time_t t = time((time_t*)&timestamp);
	time(&t);
	string time_string = ctime(&t);
	return time_string.substr(0, time_string.length()-1);
}

Timer::~Timer()
{
	this->stop();
}

AppTimer::AppTimer() : Timer()
{

}

void AppTimer::initFPSCounter()
{
	this->frame_counter = 0;
	this->frame_time = this->getTicks();
}

long AppTimer::calcDelay(long start, long stop)
{
	long time_ival = stop - start;

	if(time_ival < 1000 / FPS_LOCK)
	{
		SDL_Delay((1000 / FPS_LOCK) - time_ival);
	}
	return time_ival;
}

int AppTimer::calcFPS()
{
	int fps = 0, ival = 0;

	if((ival = (this->getTicks() - this->frame_time)) > 1000)
	{
		fps = this->frame_counter / ( ival / 1000);
	}
	if(this->frame_counter > UINT_MAX)
	{
		this->frame_counter = 0;
		this->frame_time = this->getTicks();
	}
	this->frame_counter++;
	this->fps = fps;
	return fps;
}

AppTimer::~AppTimer()
{

}