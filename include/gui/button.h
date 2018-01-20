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
            VIDEO::Texture * texture;
            std::string text;

        public:
            explicit Button(std::string text);
            Button(Object * parent, std::string text);
            std::string setText(std::string text);
            std::string getText() const;
        };
    }
}

#endif //TURBO_BUTTON_H
