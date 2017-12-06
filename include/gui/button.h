#ifndef TURBO_BUTTON_H
#define TURBO_BUTTON_H

#include "gui/widget.h"

namespace TURBO
{
    namespace GUI
    {
        class Button : public Widget
        {
        protected:
            std::string text;

        public:
            Button(Object * parent, std::string text);
            Button(std::string text);
        };
    }
}

#endif //TURBO_BUTTON_H
