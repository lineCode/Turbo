#include "gui/layout.h"

namespace TURBO
{
    namespace GUI
    {
        LayoutContainer::LayoutContainer(Object *parent)
            : Object(parent)
        {
            object_type = OBJECT_TYPE::LAYOUT;
        }

        std::vector<Object *> LayoutContainer::getChildren()
        {
            return children;
        }

        Box::Box(Object *parent, ORIENTATION orientation)
            : LayoutContainer(parent)
        {

        }

        Box *Box::addWidget(Object *object, int index)
        {
            if(index == -1)
            {
                children.push_back(object);
            }
            else
            {
                children.insert(children.begin() + index, object);
            }
            update();
            return this;
        }

        Box *Box::removeWidget(Object *object)
        {
            children.erase(std::find(children.begin(), children.end(), object));
            update();
            return this;
        }

        Box *Box::removeWidget(int index)
        {
            children.erase(children.begin() + index);
            update();
            return this;
        }

        Box *Box::update()
        {
            MATH::Rect children_size = size / children.size();
            for(auto & child : children)
            {
                child->setSize(children_size);
            }
        }
    }
}