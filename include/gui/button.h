#ifndef TURBO_BUTTON_H
#define TURBO_BUTTON_H

#include "gui/text_widget.h"

namespace TURBO
{
    namespace GUI
    {
        class Button : public TextWidget
        {
        public:
            explicit Button(std::string text);
            Button(Object * parent, std::string text);
        };
    }
}

#endif //TURBO_BUTTON_H
