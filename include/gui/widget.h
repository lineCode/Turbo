#ifndef TURBO_WIDGET_H
#define TURBO_WIDGET_H

#include <string>

#include "gui/object.h"
#include "video/font.h"

namespace TURBO
{
    namespace GUI
    {
        class Widget : public Object
        {
        private:

        public:
            explicit Widget(Object * parent);

        };
    }
}

#endif //TURBO_WIDGET_H
