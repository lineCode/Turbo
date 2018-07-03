#ifndef TURBO_SCHEDULE_H
#define TURBO_SCHEDULE_H

#include <thread>
#include <queue>

#include "util/util.h"

namespace TURBO
{
    namespace UTIL
    {
        enum class SCHEDULER_STATE
            : Uint8
        {
            STOPPED = 0x0,
            STARTED = 0x1,
            PAUSED  = 0x2
        };

        struct SchedulerTask
        {
            int                   priority;
            std::string           name;
            std::function<void()> function;
            Uint64                time;
            bool                  repeat;
        };

        template<typename T>
        class Scheduler
        {
        private:
            T                          clock;
            std::thread                thread;
            SCHEDULER_STATE            state = SCHEDULER_STATE::STOPPED;
            std::queue<SchedulerTask> tasks;

            void run()
            {
                while(state != SCHEDULER_STATE::STOPPED)
                {
                    if(!tasks.empty())
                    {

                    }
                    clock.sleep(1);
                }
            }

            void suspendTask(SchedulerTask &task)
            {

            }

        public:
            Scheduler()
            {
                thread = std::thread(run);
            }

            void addTask(SchedulerTask &task)
            {

            }

            void removeTask(SchedulerTask &task)
            {

            }
        };
    }
}

#endif //TURBO_SCHEDULE_H
