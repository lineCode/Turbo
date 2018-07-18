#include <util/log.h>
#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        int Object::objects = 0;

        Object::Object(Object *parent)
            : StyleProperties(),
              parent(parent),
              id(Object::objects++)
        {
            if(parent != nullptr)
            {
                parent->setChild(this);
                setPosition(parent->getSize().topLeft());
                setSpace(parent->getSize());
                setSize(parent->getSize());
                setContent(parent->getSize());
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
            mouse_over    = MATH::pointInRect(p, space) && !mouse_on;
            mouse_out     = !MATH::pointInRect(p, space) && mouse_on;
            mouse_clicked = INPUT::Mouse::pressed();

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
                if(mouse_on)
                {
                    fireCallback(EVENT_TYPE::ON_MOUSE_BUTTON_DOWN);
                }
            }

            if(child != nullptr)
            {
                child->pollEvent(event);
            }
        }

        void Object::registerCallback(Uint8 event, const std::function<void()> callback)
        {
            callbacks[event] = callback;
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

        MATH::Rect &Object::setSpace(MATH::Rect space)
        {
            this->space = space;
            fireCallback(ON_SPACE_CHANGED);
            return this->space;
        }

        MATH::Rect &Object::getSpace()
        {
            return space;
        }

        MATH::Rect &Object::setSize(MATH::Rect size)
        {
            if(size <= space)
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

        MATH::Rect &Object::setContent(MATH::Rect content)
        {
            if(content <= size)
            {
                this->content = content;
                fireCallback(ON_CONTENT_CHANGED);
            }
            return this->content;
        }

        MATH::Rect &Object::getContent()
        {
            return this->content;
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

        int Object::getId()
        {
            return id;
        }

        Object *Object::getParent()
        {
            return parent;
        }

        Object *Object::setParent(Object *object)
        {
            parent = object;
            fireCallback(ON_PARENT_CHANGED);
            update();
            return this;
        }

        Object *Object::getChild()
        {
            return child;
        }

        Object *Object::setChild(Object *object)
        {
            this->child = object;
            object->setParent(this);
            fireCallback(ON_CHILD_CHANGED);
            update();
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
            renderer->drawRect(space, 1, background_color, true);
            renderer->drawTexture(background_texture, space);
            renderer->drawRect(space, 1, border_color, false);
            if(child != nullptr)
            {
                child->draw(renderer);
            }
        }

        Object *Object::update()
        {
            if(parent != nullptr)
            {
                setPosition(parent->getSize().topLeft());
                setSpace(parent->getSize());
                setSize(parent->getSize());
                setContent(parent->getSize());
            }

            if(child != nullptr)
            {
                child->update();
            }
        }
    }
}