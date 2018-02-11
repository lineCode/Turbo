#include <util/log.h>
#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        Object::Object(Object *parent)
            : parent(parent),
              child(nullptr),
              geometry(),
              size(),
              object_type(OBJECT_TYPE::OBJECT),
              visible(false),
              mouse_on(false),
              mouse_over(false),
              mouse_out(false),
              mouse_clicked(false)
        {
            if(parent != nullptr)
            {
                parent->setChild(this);
                setGeometry(parent->getSize());
                // TODO Set position from parent object
                setPosition(parent->getGeometry().topLeft());
                setSize(getGeometry());
            }
        }

        Object::~Object()
        {

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
            // TODO geometry need reference to global coordinates
            mouse_over    = MATH::pointInRect(p, geometry) && !mouse_on;
            mouse_out     = !MATH::pointInRect(p, geometry) && mouse_on;
            mouse_clicked = INPUT::Mouse::pressed();

            if(child != nullptr)
            {
                child->pollEvent(event);
            }

            if(mouse_over)
            {
                mouse_on = true;
                fireCallback(EVENT_TYPE::ON_MOUSE_OVER);
            }
            if(mouse_out)
            {
                mouse_on = false;
                fireCallback(EVENT_TYPE::ON_MOUSE_OUT);
            }
            if(mouse_clicked)
            {
                std::cout << geometry.x << " " << INPUT::Mouse::getPosition().x << std::endl;
                if(mouse_on)
                {
                    fireCallback(EVENT_TYPE::ON_MOUSE_BUTTON_DOWN);
                }
            }
        }

        void Object::registerCallback(Uint8 event, const std::function<void()> callback)
        {
            callbacks[event] = callback;
        }

        MATH::Rect &Object::setGeometry(MATH::Rect geometry)
        {
            this->geometry = geometry;
            fireCallback(ON_GEOMETRY_CHANGED);
            return this->geometry;
        }

        MATH::Rect &Object::getGeometry()
        {
            return geometry;
        }

        MATH::Point &Object::setPosition(MATH::Point position)
        {
            this->position = position;
            fireCallback(ON_POSITION_CHANGED);
            return this->position;
        }

        MATH::Point &Object::getPosition()
        {
            return position;
        }

        MATH::Rect &Object::setSize(MATH::Rect size)
        {
            if(size <= geometry)
            {
                this->size = size;
                fireCallback(ON_SIZE_CHANGED);
            }
            return this->size;
        }

        MATH::Rect &Object::getSize()
        {
            return size;
        }

        OBJECT_TYPE Object::getObjectType()
        {
            return object_type;
        }

        OBJECT_TYPE Object::setObjectType(OBJECT_TYPE type)
        {
            object_type = type;
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

        bool Object::mouseOut()
        {
            return mouse_out;
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
            fireCallback(ON_PARENT_CHANGED);
            return this;
        }

        Object *Object::getChild()
        {
            return child;
        }

        Object *Object::setChild(Object *object)
        {
            this->child = object;
            fireCallback(ON_CHILD_CHANGED);
            return this;
        }

        Object *Object::hide()
        {
            visible = false;
            if(child != nullptr)
            {
                child->hide();
            }
            fireCallback(ON_VISIBILITY_CHANGED);
            return this;
        }

        Object *Object::show()
        {
            visible = true;
            if(child != nullptr)
            {
                child->show();
            }
            fireCallback(ON_VISIBILITY_CHANGED);
            return this;
        }

        Object *Object::setVisibility(bool visible)
        {
            if(visible)
            {
                show();
            }
            else
            {
                hide();
            }
            return this;
        }

        float Object::setOpacity(float alpha)
        {
            if(alpha > 0)
            {
                this->opacity = std::min(1.0f, alpha);
            }
            return this->opacity;
        }

        float Object::getOpacity()
        {
            return opacity;
        }

        void Object::draw(VIDEO::Renderer *renderer)
        {
            renderer->drawRect(size, background_color, true);
            renderer->drawTexture(background_texture, size);
            renderer->drawRect(size, border_color, false);
            if(child != nullptr)
            {
                child->draw(renderer);
            }
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