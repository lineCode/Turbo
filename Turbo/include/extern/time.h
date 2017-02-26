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
		const string 		TAG = "Timer";

	protected:
		TIMER_STATE			timer_state;
		Uint64 				timer_value;
		Uint64				ival_start;
		Uint64				ival_stop;

	public:
		Timer();
		Uint64 				getTicks();
		void 				start();
		Uint64 				pause();
		Uint64 				resume();
		Uint64 				stop();
        Uint64 				getTime();
        static void			sleep(Uint32 microseconds = 0);
		static std::string 	getTimeToString(Sint64 time = -1,
											std::string format = "hh:mm:ss DD:MM:YYYY");
		~Timer();
	};

	class AppTimer : public Timer
	{
	private:
		const string	TAG = "AppTimer";
		Uint32			frame_counter;
		Uint64 			frame_time;
        Uint16 			fps;

	public:
		AppTimer();
		void 	initFPSCounter();
		long 	calcDelay(long start, long stop);
        int 	calcFPS();
		~AppTimer();

	};

}

#endif // TIME_H_INCLUDED
