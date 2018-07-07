#include "system/signal.h"

namespace TURBO
{
    namespace SYSTEM
    {
        std::map<int, struct sigaction> SignalHandler::signals;

        void SignalHandler::addSignal(int signal, void (*f) (int))
        {
            struct sigaction handler;

            handler.sa_handler = f;
            sigemptyset(&handler.sa_mask);
            handler.sa_flags = 0;
            SignalHandler::signals.insert(std::pair<int, struct sigaction>(signal, handler));

            sigaction(signal, &SignalHandler::signals[signal], nullptr);
        }
    }
}