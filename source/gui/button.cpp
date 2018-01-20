#include "gui/button.h"

namespace TURBO
{
    namespace GUI
    {
        Button::Button(Object *parent, const std::string text)
            : Widget(parent), text(text)
        {
            setObjectType(OBJECT_TYPE::BUTTON);
        }

        Button::Button(const std::string text)
            : Widget(nullptr), text(text)
        {

        }

        std::string Button::setText(const std::string text)
        {
            this->text = text;
            return this->text;
        }

        std::string Button::getText() const
        {
            return text;
        }
    }
}