#include "gui/layout.h"

namespace TURBO
{
    namespace GUI
    {
        LayoutContainer::LayoutContainer(Object *parent)
            : Object(parent)
        {

        }

        bool LayoutContainer::addWidget(Object *object)
        {
            children.push_back(object);
        }
    }
}