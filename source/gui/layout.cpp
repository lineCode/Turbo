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
            : LayoutContainer(parent), orientation(orientation)
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
            MATH::Rect children_size = size;
            if(orientation == ORIENTATION::HORIZONTAL)
            {
                children_size.div(0, 0, children.size(), 0);
            }
            else if(orientation == ORIENTATION::VERTICAL)
            {
                children_size.div(0, 0, 0, children.size());
            }

            for(auto & child : children)
            {
                child->setGeometry(children_size);
                child->setSize(child->getGeometry());
                if(orientation == ORIENTATION::HORIZONTAL)
                {
                    children_size.add(children_size.w, 0, 0, 0);
                }
                else if(orientation == ORIENTATION::VERTICAL)
                {
                    children_size.add(0, children_size.h, 0, 0);
                }
            }
        }
    }
}