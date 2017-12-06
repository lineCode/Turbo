#include <util/log.h>
#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        Object::Object(Object * parent)
            : parent(parent), geometry()
        {

        }

        void Object::fireCallback(std::string callback)
        {
            if(callbacks.count(callback))
            {
                callbacks[callback]();
            }
        }

        void Object::pollEvent(SDL_Event &event)
        {
            MATH::Point p = INPUT::Mouse::getPosition();
            mouse_over = MATH::pointInRect(p, geometry);
            mouse_clicked = mouse_over && INPUT::Mouse::pressed();

            if(mouse_over)
            {
                fireCallback("onMouseOver");
            }
            if(mouse_clicked)
            {
                fireCallback("onClicked");
            }
        }

        MATH::Rect Object::setGeometry(MATH::Rect geometry)
        {
            this->geometry = geometry;
            return this->geometry;
        }

        MATH::Rect Object::getGeometry()
        {
            return geometry;
        }

        bool Object::isVisible()
        {
            return visible;
        }

        bool Object::mouseOver()
        {
            return mouse_over;
        }

        void Object::onMouseOver(std::function<void()> callback)
        {
            callbacks["onMouseOver"] = callback;
        }

        bool Object::mouseClicked()
        {
            return mouse_clicked;
        }

        Object & Object::show()
        {
            visible = true;
            return *this;
        }
    }
}