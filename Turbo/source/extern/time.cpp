#include "extern/time.h"

using namespace EXTERN;

Timer::Timer()
{
	this->start();
}

Uint64 Timer::getTicks()
{
	//TODO
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
	SDL_Delay(milliseconds);
	//TODOstd::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

string Timer::getTimeToString(Uint64 timestamp, string format)
{
	//time_t ti = time(&timestamp);
	//struct tm * time_info;
	//char buffer[100];
	//time_info = localtime(&ti);
	//string time_stringStrf = (string)strftime(buffer, format.c_str(), &time_info);

    /*std::time_t temp = timestamp;
    std::tm * t = std::gmtime(&temp);
    std::stringstream ss; 

    ss << std::put_time(t, format.c_str());
    return ss.str();*/
    return "[NO TIME]";
}

Timer::~Timer()
{
	this->stop();
}

AppTimer::AppTimer(Uint64 fps_lock)
	: Timer(), fps_lock(fps_lock)
{
	this->initFPSCounter();
}

void AppTimer::initFPSCounter()
{
	this->frame_counter = 0;
	this->frame_time = this->getTicks();
}

Uint64 AppTimer::calcDelay(Uint64 start, Uint64 stop)
{
	Uint64 time_ival = stop - start;

	if(time_ival < (1000 / this->fps_lock))
	{
		this->sleep((Uint32)((1000 / this->fps_lock) - time_ival));
	}
	return time_ival;
}

Uint64 AppTimer::calcFPS()
{
	Uint64 fps = 0, ival = 0;

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