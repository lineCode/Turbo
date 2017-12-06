#include "gui/button.h"

namespace TURBO
{
    namespace GUI
    {
        Button::Button(Object *parent, const std::string text)
            : Widget(parent), text(text)
        {

        }

        Button::Button(const std::string text)
            : Widget(nullptr), text(text)
        {

        }
    }
}