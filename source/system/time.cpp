#include "system/time.h"

namespace TURBO
{
    namespace SYSTEM
    {
        Uint16 Timer::timers  = 0;
        Uint16 PTimer::timers = 0;

        typedef std::chrono::system_clock system_clock;
        typedef std::chrono::nanoseconds  nanoseconds;
        typedef std::chrono::microseconds microseconds;
        typedef std::chrono::milliseconds milliseconds;
        typedef std::chrono::seconds      seconds;

        Uint32 Time::getTicks()
        {
            return SDL_GetTicks();
        }

        Uint64 Time::getTimestamp()
        {
            auto ns = std::chrono::duration_cast<nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
            return static_cast<Uint64>(ns.count());
        }

        void Time::sleep(Uint64 ns)
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds(ns));
        }

        std::string Time::getTicksToString(Uint32 ticks, std::string format)
        {
            std::stringstream ss;
            Sint32            digits      = 0;
            Uint64            offset      = 0;
            Uint64            next_offset = 0;
            Uint64            diff        = 0;
            Uint64            hours       = 0, minutes = 0, seconds = 0, milliseconds = 0;

            if((offset = format.find("%H", offset)) != std::string::npos)
            {
                hours  = ticks / (1000 * 60 * 60);
                diff   = hours * 1000 * 60 * 60;
                digits = UTIL::digits(hours);

                ss << std::setw(std::max(2, digits)) << std::setfill('0') << hours
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }
            if((offset = format.find("%M", next_offset)) != std::string::npos)
            {
                minutes = (hours > 0) ? ticks / (1000 * 60) % 60 : ticks / (1000 * 60);
                digits  = UTIL::digits(minutes);

                ss << std::setw(std::max(2, digits)) << std::setfill('0') << minutes
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }
            if((offset = format.find("%S", next_offset)) != std::string::npos)
            {
                seconds = (minutes > 0) ? (ticks / 1000 % 60) : (ticks - diff) / 1000;
                digits  = UTIL::digits(seconds);

                ss << std::setw(std::max(2, digits)) << std::setfill('0') << seconds
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }

            diff += minutes * 1000 * 60;

            if((offset = format.find("%f", next_offset)) != std::string::npos)
            {
                milliseconds = (seconds > 0) ? (ticks % 1000) : ticks - diff;
                digits       = UTIL::digits(milliseconds);

                ss << std::setw(std::max(3, digits)) << std::setfill('0') << milliseconds
                   << format.substr(offset + 2);
            }
            return ss.str();
        }

        std::string Time::getPTicksToString(Uint64 ticks, std::string format)
        {
            std::stringstream ss;
            Sint32            digits      = 0;
            Uint64            offset      = 0;
            Uint64            next_offset = 0;
            Uint64            diff        = 0;
            Uint64            hours       = 0, minutes = 0, seconds = 0, milliseconds = 0, microseconds = 0, nanoseconds = 0;
            Uint64            ns_to_s     = 1000 * 1000 * 1000;

            if((offset = format.find("%H", offset)) != std::string::npos)
            {
                hours  = (ticks / (ns_to_s * 60 * 60));
                diff   = hours * ns_to_s * 60 * 60;
                digits = UTIL::digits(hours);

                ss << std::setw(std::max(2, digits)) << std::setfill('0') << hours
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }
            if((offset = format.find("%M", next_offset)) != std::string::npos)
            {
                minutes = (hours > 0) ? (ticks / (ns_to_s * 60)) % 60 : ticks / (ns_to_s * 60);
                digits  = UTIL::digits(minutes);

                ss << std::setw(std::max(2, digits)) << std::setfill('0') << minutes
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }
            if((offset = format.find("%S", next_offset)) != std::string::npos)
            {
                seconds = (minutes > 0) ? (ticks / ns_to_s) % 60 : (ticks - diff) / ns_to_s;
                digits  = UTIL::digits(seconds);

                ss << std::setw(std::max(2, digits)) << std::setfill('0') << seconds
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }

            diff += minutes * ns_to_s * 60;

            if((offset = format.find("%f", next_offset)) != std::string::npos)
            {
                milliseconds = (seconds > 0) ? (ticks / (1000 * 1000)) % 1000 : (ticks - diff) / (1000 * 1000);
                digits       = UTIL::digits(milliseconds);

                ss << std::setw(std::max(3, digits)) << std::setfill('0') << milliseconds
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }

            diff += seconds * ns_to_s;

            if((offset = format.find("%u", next_offset)) != std::string::npos)
            {
                microseconds = (milliseconds > 0) ? (ticks / 1000) % 1000 : (ticks - diff) / 1000;
                digits       = UTIL::digits(microseconds);

                ss << std::setw(std::max(3, digits)) << std::setfill('0') << microseconds
                   << format.substr(offset + 2, format.find('%', offset + 2) - offset - 2);
                next_offset = offset + 2;
            }

            diff += milliseconds * 1000 * 1000;

            if((offset = format.find("%n", next_offset)) != std::string::npos)
            {
                nanoseconds = (microseconds > 0) ? ticks % 1000 : ticks - diff;
                digits      = UTIL::digits(nanoseconds);

                ss << std::setw(std::max(3, digits)) << std::setfill('0') << nanoseconds
                   << format.substr(offset + 2);
            }
            return ss.str();
        }

        std::string Time::getTimestampToString(Uint64 timestamp, std::string format)
        {
            const auto                                  ns   = nanoseconds(timestamp);
            const std::chrono::time_point<system_clock> tp(ns);
            time_t                                      time = system_clock::to_time_t(tp);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), format.c_str());
            return ss.str();
        }

        Timer::Timer()
        {
            Timer::timers++;
            timer_id = Timer::timers;

            start();
        }

        Uint32 Timer::start()
        {
            timer_started = getTicks();
            if(state != TIMER_STATE::STARTED)
            {
                elapsed_time = 0;
                state        = TIMER_STATE::STARTED;
            }
            else
            {
                state = TIMER_STATE::STOPPED;
                return start();
            }
            return timer_started;
        }

        Uint32 Timer::pause()
        {
            timer_paused = getTicks();
            if(state == TIMER_STATE::STARTED)
            {
                Uint32 time_diff = timer_paused - timer_started;
                active_time += time_diff;
                elapsed_time += time_diff;
                state            = TIMER_STATE::PAUSED;
            }
            return timer_paused;
        }

        Uint32 Timer::resume()
        {
            timer_resumed = getTicks();
            if(state == TIMER_STATE::PAUSED)
            {
                Uint32 time_diff = timer_resumed - timer_paused;
                paused_time += time_diff;
                elapsed_time += time_diff;
                state            = TIMER_STATE::STARTED;
            }
            return timer_resumed;
        }

        Uint32 Timer::stop()
        {
            timer_stopped = getTicks();
            if(state != TIMER_STATE::STOPPED)
            {
                Uint32 diff_time = (timer_resumed > timer_started) ? timer_resumed : timer_started;
                if(state != TIMER_STATE::PAUSED)
                {
                    active_time += timer_stopped - diff_time;
                }
                elapsed_time += timer_stopped - diff_time;
                state            = TIMER_STATE::STOPPED;
            }
            return timer_stopped;
        }

        Uint32 Timer::addTime(Uint32 amount)
        {
            elapsed_time += amount;

            return elapsed_time;
        }

        Uint32 Timer::addActiveTime(Uint32 amount)
        {
            active_time += amount;
            elapsed_time += amount;

            return active_time;
        }

        Uint32 Timer::subTime(Uint32 amount)
        {
            elapsed_time -= amount;

            return elapsed_time;
        }

        Uint32 Timer::subActiveTime(Uint32 amount)
        {
            active_time -= amount;
            elapsed_time -= amount;

            return active_time;
        }

        TIMER_STATE Timer::reset()
        {
            stop();
            elapsed_time = 0;
            active_time  = 0;
            paused_time  = 0;
            return state;
        }

        TIMER_STATE Timer::getState()
        {
            return state;
        }

        Uint32 Timer::getTicks()
        {
            return Time::getTicks();
        }

        Uint32 Timer::getTime()
        {
            pause();
            resume();
            return elapsed_time;
        }

        Uint32 Timer::getActiveTime()
        {
            pause();
            resume();
            return active_time;
        }

        Uint32 Timer::getPausedTime()
        {
            pause();
            resume();
            return paused_time;
        }

        std::string Timer::printTime()
        {
            std::vector<std::string> states = {"stopped", "started", "paused"};
            std::ostringstream       oss;
            oss << "\nTimer " << timer_id
                << "\nTimer state:      " << states.at(static_cast<Uint8>(state))
                << "\nTime active:      " << active_time << " ms"
                << "\nTime paused:      " << paused_time << " ms"
                << "\nTime since start: " << elapsed_time << std::endl;
            return oss.str();
        }

        Timer::~Timer()
        {
            stop();
        }

        PTimer::PTimer()
        {
            PTimer::timers++;
            timer_id = PTimer::timers;

            start();
        }

        PTimer::~PTimer()
        {
            stop();
        }

        Uint64 PTimer::start()
        {
            timer_started = getTicks();
            if(state != TIMER_STATE::STARTED)
            {
                elapsed_time = 0;
                state        = TIMER_STATE::STARTED;
            }
            else
            {
                state = TIMER_STATE::STOPPED;
                return start();
            }
            return timer_started;
        }

        Uint64 PTimer::pause()
        {
            timer_paused = getTicks();
            if(state == TIMER_STATE::STARTED)
            {
                Uint64 time_diff = timer_paused - timer_started;
                active_time += time_diff;
                elapsed_time += time_diff;
                state            = TIMER_STATE::PAUSED;
            }
            return timer_paused;
        }

        Uint64 PTimer::resume()
        {
            timer_resumed = getTicks();
            if(state == TIMER_STATE::PAUSED)
            {
                Uint64 time_diff = timer_resumed - timer_paused;
                paused_time += time_diff;
                elapsed_time += time_diff;
                state            = TIMER_STATE::STARTED;
            }
            return timer_resumed;
        }

        Uint64 PTimer::stop()
        {
            timer_stopped = getTicks();
            if(state != TIMER_STATE::STOPPED)
            {
                Uint64 diff_time = (timer_resumed > timer_started) ? timer_resumed : timer_started;
                if(state != TIMER_STATE::PAUSED)
                {
                    active_time += timer_stopped - diff_time;
                }
                elapsed_time += timer_stopped - diff_time;
                state            = TIMER_STATE::STOPPED;
            }
            return timer_stopped;
        }

        Uint64 PTimer::addTime(Uint64 amount)
        {
            elapsed_time += amount;

            return elapsed_time;
        }

        Uint64 PTimer::addActiveTime(Uint64 amount)
        {
            active_time += amount;
            elapsed_time += amount;

            return active_time;
        }

        Uint64 PTimer::subTime(Uint64 amount)
        {
            elapsed_time -= amount;

            return elapsed_time;
        }

        Uint64 PTimer::subActiveTime(Uint64 amount)
        {
            active_time -= amount;
            elapsed_time -= amount;

            return active_time;
        }

        TIMER_STATE PTimer::reset()
        {
            stop();
            elapsed_time = 0;
            active_time  = 0;
            paused_time  = 0;
            return state;
        }

        TIMER_STATE PTimer::getState()
        {
            return state;
        }

        Uint64 PTimer::getTicks()
        {
            auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch());
            return static_cast<Uint64>(ns.count());
        }

        Uint64 PTimer::getTime()
        {
            pause();
            resume();
            return elapsed_time;
        }

        Uint64 PTimer::getActiveTime()
        {
            pause();
            resume();
            return active_time;
        }

        Uint64 PTimer::getPausedTime()
        {
            pause();
            resume();
            return paused_time;
        }

        std::string PTimer::printTime()
        {
            std::vector<std::string> states = {"stopped", "started", "paused"};
            std::ostringstream       oss;
            oss << "\nTimer " << timer_id
                << "\nTimer state:      " << states.at(static_cast<Uint8>(state))
                << "\nTime active:      " << active_time << " ms"
                << "\nTime paused:      " << paused_time << " ms"
                << "\nTime since start: " << elapsed_time << std::endl;
            return oss.str();
        }

        TimerCallback::TimerCallback(const std::function<void()> callback, Uint32 delay)
            : callback(callback), delay(delay)
        {
            t = new std::thread(&TimerCallback::trigger, this, delay);
        }

        Uint32 TimerCallback::trigger(Uint32 delay)
        {
            SDL_Delay(delay);
            this->callback();
        }

        TimerCallback::~TimerCallback()
        {
            if(t->joinable())
            {
                t->join();
            }
            delete t;
        }
    }
}