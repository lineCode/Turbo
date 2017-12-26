#ifndef TURBO_TIMER_H
#define TURBO_TIMER_H

#include <thread>
#include <chrono>
#include <iomanip>
#include <vector>
#include <sstream>

#include "system/system_def.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class Time
        {
        public:
            static Uint32 getTicks();
            static Uint64 getTimestamp();
            static void sleep(Uint64 ns);
            static std::string getTicksToString(Uint32 ticks, std::string format = "%H:%M:%S.%f");
            static std::string getPTicksToString(Uint64 ticks, std::string format = "%H:%M:%S.%f %u %n");
            static std::string getTimestampToString(Uint64 timestamp, std::string format = "%H:%M:%S %d.%m.%Y");
        };

        /**
         * A millisecond accurate timer
         * @note the actual time may differ by some offset caused by function calls
         */
        class Timer
        {
        private:
            static Uint16   timers;
            Uint16          timer_id        = 0;
            TIMER_STATE     state           = TIMER_STATE::STOPPED;
            Uint32          elapsed_time    = 0;
            Uint32          active_time     = 0;
            Uint32          paused_time     = 0;
            Uint32          timer_started   = 0;
            Uint32          timer_paused    = 0;
            Uint32          timer_resumed   = 0;
            Uint32          timer_stopped   = 0;

        public:
            explicit Timer();
            ~Timer();
            Uint32 				start();
            Uint32 				pause();
            Uint32 				resume();
            Uint32 				stop();
            Uint32              addTime(Uint32 amount);
            Uint32              addActiveTime(Uint32 amount);
            Uint32              subTime(Uint32 amount);
            Uint32              subActiveTime(Uint32 amount);
            TIMER_STATE         reset();
            TIMER_STATE         getState();
            Uint32              getTicks();
            Uint32 				getTime();
            Uint32 				getActiveTime();
            Uint32 				getPausedTime();
            std::string         printTime();
        };

        /**
         * A nanosecond accurate pointer
         * @note the actual time may differ by some offset caused by function calls
         */
        class PTimer
        {
        private:
            static Uint16   timers;
            Uint16          timer_id        = 0;
            TIMER_STATE     state           = TIMER_STATE::STOPPED;
            Uint64          elapsed_time    = 0;
            Uint64          active_time     = 0;
            Uint64          paused_time     = 0;
            Uint64          timer_started   = 0;
            Uint64          timer_paused    = 0;
            Uint64          timer_resumed   = 0;
            Uint64          timer_stopped   = 0;

        public:
            explicit PTimer();
            ~PTimer();
            Uint64 				start();
            Uint64 				pause();
            Uint64 				resume();
            Uint64 				stop();
            Uint64              addTime(Uint64 amount);
            Uint64              addActiveTime(Uint64 amount);
            Uint64              subTime(Uint64 amount);
            Uint64              subActiveTime(Uint64 amount);
            TIMER_STATE         reset();
            TIMER_STATE         getState();
            Uint64              getTicks();
            Uint64 				getTime();
            Uint64 				getActiveTime();
            Uint64 				getPausedTime();
            std::string         printTime();
        };

        class TimerCallback
        {
            std::thread * t;
            std::thread::id parent_id;
            std::function<void()> callback;
            Uint32 delay;
            Uint32 repeat;

        public:
            explicit TimerCallback(std::function<void()> callback, Uint32 delay, Uint32 repeat = 0);
            Uint32 trigger(Uint32 delay);
            ~TimerCallback();
        };
    }
}

#endif //TURBO_TIMER_H
