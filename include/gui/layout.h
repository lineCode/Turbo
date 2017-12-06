#ifndef TURBO_LAYOUT_H
#define TURBO_LAYOUT_H

#include <vector>

#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        enum class SIZE_POLICY : Uint8
        {
            MAXIMUM = 0x0,
            MINIMUM = 0x1

        };

        class LayoutContainer : public Object
        {
        protected:
            std::vector<Object*> children;
        public:
            LayoutContainer(Object * parent);
            bool addWidget(Object * object);
        };
    }
}

#endif //TURBO_LAYOUT_H
