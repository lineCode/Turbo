#include <util/log.h>
#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        Object::Object(Object * parent)
            : parent(parent),
              child(nullptr),
              geometry(),
              object_type(OBJECT_TYPE::OBJECT),
              visible(false),
              mouse_over(false),
              mouse_clicked(false)
        {
            if(parent != nullptr)
            {
                //TODO handle size
                setSize(parent->getSize());
            }
        }

        void Object::fireCallback(Uint8 event)
        {
            if(callbacks.count(event))
            {
                callbacks[event]();
            }
        }

        void Object::pollEvent(SDL_Event &event)
        {
            MATH::Point p = INPUT::Mouse::getPosition();
            mouse_over = MATH::pointInRect(p, geometry);
            mouse_clicked = mouse_over && INPUT::Mouse::pressed();

            if(mouse_over)
            {
                fireCallback(EVENT_TYPE::ON_MOUSE_OVER);
            }
            if(mouse_clicked)
            {
                fireCallback(EVENT_TYPE::ON_MOUSE_BUTTON_DOWN);
            }
        }

        void Object::registerCallback(Uint8 event, std::function<void()> &callback)
        {
            callbacks[event] = callback;
        }

        MATH::Rect &Object::setGeometry(MATH::Rect geometry)
        {
            this->geometry = geometry;
            return this->geometry;
        }

        MATH::Rect &Object::getGeometry()
        {
            return geometry;
        }

        MATH::Rect &Object::setSize(MATH::Rect size)
        {
            if(size <= geometry)
            {
                this->size = size;
            }
            return this->size;
        }

        MATH::Rect &Object::getSize()
        {
            return size;
        }

        OBJECT_TYPE Object::getType()
        {
            return object_type;
        }

        bool Object::isVisible()
        {
            return visible;
        }

        bool Object::mouseOver()
        {
            return mouse_over;
        }

        bool Object::mouseClicked()
        {
            return mouse_clicked;
        }

        Object *Object::getParent()
        {
            return parent;
        }

        Object *Object::setParent(Object *object)
        {
            parent = object;
            return this;
        }

        Object *Object::getChild()
        {
            return child;
        }

        Object *Object::setChild(Object *object)
        {
            this->child = object;
            return this;
        }

        Object *Object::hide()
        {
            visible = false;
            if(child != nullptr)
            {
                child->hide();
            }
            return this;
        }

        Object *Object::show()
        {
            visible = true;
            if(child != nullptr)
            {
                child->show();
            }
            return this;
        }

        Object *Object::update()
        {
            if(child != nullptr)
            {
                child->update();
            }
        }
    }
}