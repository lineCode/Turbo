#include "gui/button.h"

namespace TURBO
{
    namespace GUI
    {
        Button::Button(Object *parent, const std::string text)
            : TextWidget(parent, text)
        {
            setObjectType(OBJECT_TYPE::BUTTON);
        }

        Button::Button(const std::string text)
            : TextWidget(nullptr, text)
        {

        }
    }
}