#ifndef TURBO_TIME_H
#define TURBO_TIME_H

#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <functional>
#include <sstream>

#include "system/system_def.h"
#include "util/number.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class Clock
        {
        public:
            /**
             * @brief Returns the number ticks since the application is running. (eqvivalent to SDL_GetTicks())
             * @return ticks as int
             */
            static Uint32 getTicks();

            /**
             * @brief Returns the current timestamp in nanoseconds. Uses std::chrono as reference.
             * @return timestamp as long
             */
            static Uint64 getTimestamp();

            /**
             * @brief Lets the current thread sleep for @param ns nanoseconds.
             * @param ns time to sleep in nanoseconds
             */
            static void sleep(Uint64 ns);

            /**
             * @brief Converts the number of ticks into human readable time.
             * @param ticks number of ticks to convert
             * @param format the format the resulting string shall have
             * @return a formatted string
             */
            static std::string getTicksToString(Uint32 ticks, std::string format = "%H:%M:%S.%f");

            /**
             * @brief Converts the number of performance ticks into human readable time.
             * In cotrary to @see getTicksToString this function uses 64 bit integers for higher accuracy.
             * @param ticks number of ticks to convert
             * @param format the format the resulting string shall have
             * @return a formatted string
             */
            static std::string getPTicksToString(Uint64 ticks, std::string format = "%H:%M:%S.%f %u %n");

            /**
             * @brief Converts the current timestamp into a human readable date.
             * @param timestamp the timestamp to convert
             * @param format the format the resulting string shall have
             * @return a formatted string
             */
            static std::string getTimestampToString(Uint64 timestamp, std::string format = "%H:%M:%S %d.%m.%Y");
        };

        /**
         * @brief A millisecond accurate timer
         * @note the actual time may differ by some offset caused by function calls
         */
        class Timer
        {
        private:
            static Uint16 timers;
            Uint16        timer_id      = 0;
            TIMER_STATE   state         = TIMER_STATE::STOPPED;
            Uint32        elapsed_time  = 0;
            Uint32        active_time   = 0;
            Uint32        paused_time   = 0;
            Uint32        timer_started = 0;
            Uint32        timer_paused  = 0;
            Uint32        timer_resumed = 0;
            Uint32        timer_stopped = 0;

        public:
            explicit Timer();

            ~Timer();

            Uint32 start();

            Uint32 pause();

            Uint32 resume();

            Uint32 stop();

            Uint32 addTime(Uint32 amount);

            Uint32 addActiveTime(Uint32 amount);

            Uint32 subTime(Uint32 amount);

            Uint32 subActiveTime(Uint32 amount);

            TIMER_STATE reset();

            TIMER_STATE getState();

            Uint32 getTicks();

            Uint32 getTime();

            Uint32 getActiveTime();

            Uint32 getPausedTime();

            std::string printTime();
        };

        /**
         * @brief A nanosecond accurate pointer
         * @note the actual time may differ by some offset caused by function calls.
         */
        class PTimer
        {
        private:
            static Uint16 timers;
            Uint16        timer_id      = 0;
            TIMER_STATE   state         = TIMER_STATE::STOPPED;
            Uint64        elapsed_time  = 0;
            Uint64        active_time   = 0;
            Uint64        paused_time   = 0;
            Uint64        timer_started = 0;
            Uint64        timer_paused  = 0;
            Uint64        timer_resumed = 0;
            Uint64        timer_stopped = 0;

        public:
            explicit PTimer();

            ~PTimer();

            Uint64 start();

            Uint64 pause();

            Uint64 resume();

            Uint64 stop();

            Uint64 addTime(Uint64 amount);

            Uint64 addActiveTime(Uint64 amount);

            Uint64 subTime(Uint64 amount);

            Uint64 subActiveTime(Uint64 amount);

            TIMER_STATE reset();

            TIMER_STATE getState();

            Uint64 getTicks();

            Uint64 getTime();

            Uint64 getActiveTime();

            Uint64 getPausedTime();

            std::string printTime();
        };

        /**
         * This class calls a function after a certain delay.
         */
        class TimerCallback
        {
        private:
            std::thread *t;
            std::function<void()> callback;
            Uint32                delay;

            Uint32 trigger(Uint32 delay);

        public:
            explicit TimerCallback(std::function<void()> callback, Uint32 delay);

            ~TimerCallback();
        };
    }
}

#endif //TURBO_TIME_H
