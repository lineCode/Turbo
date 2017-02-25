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

void Timer::start()
{
	this->timer_value = 0;
	this->ival_start = this->getTicks();
	this->timer_state = TIMER_STATE::STARTED;
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
	if(this->timer_state == TIMER_STATE:PAUSED)
	{
		this->ival_start = this->getTicks();
		this->timer_state = TIMER_STATE::STARTED;
	}
	return this->ivalStart;
}

Uint64 Timer::stop()
{
	if(this->timer_state != TIMER_STATE::IDLE && this->timer_state != TIMER_STATE::STOPPED)
	{
		this->timer_state = TIMER_STATE::STOPPED;
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

string Timer::getTimeToString(Sint64 time, string format)
{
	time_t t;
	time(&t);
	String timeString = ctime(&t);
	return timeString.substr(0, timeString.length()-1);
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
	this->frameCounter = 0;
	this->frameTime = this->getTicks();
}

long AppTimer::calcDelay(long start, long stop)
{
	long timeIVal = stop - start;

	if(timeIVal < 1000 / FPS_LOCK)
			SDL_Delay((1000 / FPS_LOCK) - timeIVal);
	return timeIVal;
}

int AppTimer::calcFPS()
{
	int fps = 0, ival = 0;

	if((ival = (this->getTicks() - this->frameTime)) > 1000)
	{
		fps = this->frameCounter / ( ival / 1000);
	}
	if(this->frameCounter > BIT_16)
	{
		this->frameCounter = 0;
		this->frameTime = this->getTicks();
	}
	this->frameCounter++;
	this->fps = fps;
	return fps;
}

AppTimer::~AppTimer()
{

}