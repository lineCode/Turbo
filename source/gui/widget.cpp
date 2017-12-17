#include "gui/widget.h"

namespace TURBO
{
    namespace GUI
    {
        Widget::Widget(Object *parent)
            : Object(parent)
        {
            object_type = OBJECT_TYPE::WIDGET;
        }
    }
}