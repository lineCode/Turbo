#ifndef TURBO_SIGNAL_H
#define TURBO_SIGNAL_H

#include <map>
#include <csignal>
#include <functional>

#include "system/system_def.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class SignalHandler
        {
        private:
            static std::map<int, struct sigaction> signals;

        public:
            static void addSignal(int signal, void (*f) (int));
        };
    }
}

#endif //TURBO_SIGNAL_H
