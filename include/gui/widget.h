#ifndef TURBO_WIDGET_H
#define TURBO_WIDGET_H

#include <string>

#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        class Widget : public Object
        {
        public:
            explicit Widget(Object * parent);

        };
    }
}

#endif //TURBO_WIDGET_H
