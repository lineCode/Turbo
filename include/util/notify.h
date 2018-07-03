#ifndef TURBO_NOTIFY_H
#define TURBO_NOTIFY_H

#include <vector>

#include "util/util.h"

namespace TURBO
{
    namespace UTIL
    {
        class Observer
        {
        public:
            virtual void update() = 0;
        };

        class Observeable
        {
        private:
            std::vector<Observer> observer;

        public:
            void attach(Observer &o);
            void detach(Observer &o);
            void notify();
        };
    }
}

#endif //TURBO_NOTIFY_H
