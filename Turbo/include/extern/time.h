#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

/**
*** @package 	time
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The time package contains timers :
***
***
**/

#include "extern/extern.h"

namespace EXTERN
{
	/**
	*** @class Timer
	***
	*** @var	timer_state		stores the current timer state
	*** @var 	timer_value		stores the milliseconds since creation
	*** @var	ival_start		stores the timestamp of the last start or resume
	*** @var	ival_stop		stores the timestamp of the last stop or pause
	**/
	class Timer
	{
	private:
		const std::string 		TAG = "Timer";

	protected:
		TIMER_STATE			timer_state = TIMER_STATE::STOPPED;
		Uint64 				timer_value;
		Uint64				ival_start;
		Uint64				ival_stop;

	public:
		Timer();
		Uint64 				getTicks();
		Uint64 				start();
		Uint64 				pause();
		Uint64 				resume();
		Uint64 				stop();
        Uint64 				getTime();
        static void			sleep(Uint32 microseconds = 0);
		static std::string 	getTimeToString(Uint64 timestamp = 0,
											std::string format = "%H:%M:%S %D-%m-%Y");
		~Timer();
	};

	class AppTimer : public Timer
	{
	private:
		const std::string	TAG = "AppTimer";
		Uint64			fps_lock;
		Uint64			frame_counter;
		Uint64 			frame_time;
        Uint64 			fps;

	public:
		AppTimer(Uint64 fps_lock);
		void 	initFPSCounter();
		Uint64 	calcDelay(Uint64 start, Uint64 stop);
        Uint64 	calcFPS();
		~AppTimer();

	};

}

#endif // TIME_H_INCLUDED
