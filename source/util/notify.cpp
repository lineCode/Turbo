#include "util/notify.h"

namespace TURBO
{
    namespace UTIL
    {
        void Observeable::attach(Observer &o)
        {
            //observer.emplace_back(o);
        }

        void Observeable::detach(Observer &o)
        {
            //observer.erase(std::find(observer.begin(), observer.end(), o));
        }

        void Observeable::notify()
        {
            for(auto & o : observer)
            {
                o.update();
            }
        }
    }
}