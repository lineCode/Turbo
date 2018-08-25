#include <util/log.h>
#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        int Object::objects = 0;

        Object::Object(Object *parent)
            : parent(parent),
              id(Object::objects++)
        {
            if(parent != nullptr)
            {
                parent->setChild(this);
            }
            else
            {
                update();
            }
        }

        Object::~Object()
        {

        }

        void Object::dispatchEvent(Uint8 event)
        {
            if(callbacks.count(event))
            {
                callbacks[event]();
            }
        }

        void Object::pollEvent(SDL_Event *event)
        {
            MATH::Point p = INPUT::Mouse::getPosition();
            mouse_over    = MATH::pointInRect(p, space) && !mouse_on;
            mouse_out     = !MATH::pointInRect(p, space) && mouse_on;
            mouse_clicked = false;
            mouse_moving  = false;
            wheel_moving  = false;

            if(mouse_over)
            {
                mouse_on = true;
                dispatchEvent(EVENT_TYPE::ON_MOUSE_OVER);
            }
            if(mouse_out)
            {
                mouse_on = false;
                dispatchEvent(EVENT_TYPE::ON_MOUSE_OUT);
            }
            if(mouse_on)
            {
                if(event->type == SDL_MOUSEMOTION)
                {
                    mouse_moving = true;
                    dispatchEvent(EVENT_TYPE::ON_MOUSE_MOVING);
                }
                else if(event->type == SDL_MOUSEWHEEL)
                {
                    wheel_moving = true;
                }

                mouse_clicked = INPUT::Mouse::pressed();
                dispatchEvent(EVENT_TYPE::ON_MOUSE_BUTTON_DOWN);
            }

            if(child != nullptr)
            {
                child->pollEvent(event);
            }
        }

        void Object::addEventListener(Uint8 event, std::function<void()> callback)
        {
            callbacks[event] = std::move(callback);
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

        bool Object::mouseMoving()
        {
            return mouse_moving;
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

        bool Object::wheelMoving()
        {
            return wheel_moving;
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
            dispatchEvent(ON_PARENT_CHANGED);
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
            dispatchEvent(ON_CHILD_CHANGED);
            update();
            return this;
        }

        void Object::draw(VIDEO::Renderer *renderer)
        {
            renderer->drawRect(space, 1, background_color, true);
            renderer->drawTexture(background_texture, background_texture_rect);
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
                setSpace(parent->getSpace());
                setSize(parent->getSpace());
                setContent(parent->getSpace());
                setBackgroundTextureRect(parent->getSpace());
            }

            if(child != nullptr)
            {
                child->update();
            }
            return this;
        }

        MATH::Point &Object::setPosition(MATH::Point position)
        {
            this->position = position;
            dispatchEvent(EVENT_TYPE::ON_POSITION_CHANGED);
            return this->position;
        }

        MATH::Point &Object::getPosition()
        {
            return position;
        }

        MATH::Rect &Object::setSpace(MATH::Rect space)
        {
            this->space = space;
            dispatchEvent(EVENT_TYPE::ON_SPACE_CHANGED);
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
                dispatchEvent(EVENT_TYPE::ON_SIZE_CHANGED);
                this->size = size;
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
                dispatchEvent(EVENT_TYPE::ON_CONTENT_CHANGED);
                this->content = content;
            }

            if(background_texture != nullptr)
            {
                SDL_Rect   tex = background_texture->getSize();
                MATH::Rect tex_rect(0, 0, tex.w, tex.h);

                background_texture_rect = MATH::Rect(content.x, content.y, tex_rect.w, tex_rect.h);
            }
            return this->content;
        }

        MATH::Rect &Object::getContent()
        {
            return this->content;
        }

        Uint8 Object::setFontSize(Uint8 size)
        {
            font_size = size;
            return font_size;
        }

        Uint8 Object::getFontSize()
        {
            return font_size;
        }

        VIDEO::FONT_STYLE Object::setFontStyle(VIDEO::FONT_STYLE style)
        {
            font_style = style;
            return font_style;
        }

        VIDEO::FONT_STYLE Object::getFontStyle()
        {
            return font_style;
        }

        VIDEO::TEXT_WRAPPING Object::setTextWrapping(VIDEO::TEXT_WRAPPING wrapping)
        {
            text_wrapping = wrapping;
            return text_wrapping;
        }

        VIDEO::TEXT_WRAPPING Object::getTextWrapping()
        {
            return text_wrapping;
        }

        VIDEO::TEXT_ALIGNMENT Object::setTextAlignment(VIDEO::TEXT_ALIGNMENT alignment)
        {
            text_alignment = alignment;
            return text_alignment;
        }

        VIDEO::TEXT_ALIGNMENT Object::getTextAlignment()
        {
            return text_alignment;
        }

        VIDEO::Texture *Object::getBackgroundTexture()
        {
            return background_texture;
        }

        VIDEO::Texture *Object::setBackgroundTexture(const std::string path, VIDEO::Renderer *renderer)
        {
            VIDEO::Surface surface = VIDEO::Surface(path, renderer);
            background_texture = new VIDEO::Texture(renderer->getRenderer(), surface.getSurface());

            if(background_texture != nullptr)
            {
                SDL_Rect   tex = background_texture->getSize();
                MATH::Rect tex_rect(0, 0, tex.w, tex.h);

                Sint32 max_width  = std::max(tex.w, space.w);
                Sint32 max_height = std::max(tex.h, space.h);

                float width_factor  = tex.w / std::max(space.w, 1);
                float height_factor = tex.h / std::max(space.h, 1);

                float factor = (width_factor > height_factor) ? width_factor : height_factor;

                background_texture_rect = MATH::Rect(content.x, content.y,
                                                     static_cast<Sint32>(tex_rect.w / factor),
                                                     static_cast<Sint32>(tex_rect.h / factor));
            }
            return background_texture;
        }

        MATH::Rect Object::getBackgroundTextureRect()
        {
            return background_texture_rect;
        }

        MATH::Rect Object::setBackgroundTextureRect(MATH::Rect rect)
        {
            if(background_texture != nullptr)
            {
                SDL_Rect   tex = background_texture->getSize();
                MATH::Rect tex_rect(0, 0, tex.w, tex.h);

                Sint32 max_width  = std::max(tex.w, std::max(rect.w, 1));
                Sint32 max_height = std::max(tex.h, std::max(rect.h, 1));

                float width_factor  = tex.w / std::max(rect.w, 1);
                float height_factor = tex.h / std::max(rect.h, 1);

                float factor = (width_factor > height_factor) ? width_factor : height_factor;

                background_texture_rect = MATH::Rect(rect.x, rect.y,
                                                     static_cast<Sint32>(tex_rect.w / factor),
                                                     static_cast<Sint32>(tex_rect.h / factor));
            }
            return background_texture_rect;
        }

        VIDEO::Color Object::getBackgroundColor()
        {
            return background_color;
        }

        VIDEO::Color Object::setBackgroundColor(VIDEO::Color color)
        {
            background_color = color;
            return background_color;
        }

        VIDEO::Color Object::getTextColor()
        {
            return text_color;
        }

        VIDEO::Color Object::setTextColor(VIDEO::Color color)
        {
            text_color = color;
            return text_color;
        }

        VIDEO::Color Object::getBorderColor()
        {
            return border_color;
        }

        VIDEO::Color Object::setBorderColor(VIDEO::Color color)
        {
            border_color = color;
            return border_color;
        }

        MATH::Space Object::getMargin()
        {
            return margin;
        }

        MATH::Space Object::setMargin(MATH::Space margin)
        {
            this->margin = margin;
            return margin;
        }

        MATH::Space Object::getPadding()
        {
            return padding;
        }

        MATH::Space Object::setPadding(MATH::Space padding)
        {
            this->padding = padding;
            return padding;
        }

        bool Object::isVisible()
        {
            return visible;
        }

        Object *Object::hide()
        {
            visible = false;
            if(child != nullptr)
            {
                child->hide();
            }
            dispatchEvent(ON_VISIBILITY_CHANGED);
            return this;
        }

        Object *Object::show()
        {
            visible = true;
            if(child != nullptr)
            {
                child->show();
            }
            dispatchEvent(ON_VISIBILITY_CHANGED);
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
            if(alpha >= 0 && alpha <= 1)
            {
                this->opacity = alpha;
                auto opacity = static_cast<Uint8>(alpha * 255);

                std::cout << (int) opacity << " " << (int) static_cast<Uint8>(text_opacity * 255) << std::endl;

                setBorderColor(border_color.toHexColor() & (0xFFFFFF00 | opacity));
                setBackgroundColor(background_color.toHexColor() & (0xFFFFFF00 | opacity));
                setTextOpacity(alpha);
                setBackgroundTextureOpacity(alpha);
            }
            return this->opacity;
        }

        float Object::getOpacity()
        {
            return opacity;
        }

        float Object::setTextOpacity(float alpha)
        {
            if(alpha >= 0 && alpha <= 1)
            {
                text_opacity = alpha;
                auto opacity = static_cast<Uint8>(alpha * 255);
                setTextColor(text_color.toHexColor() & (0xFFFFFF00 | opacity));
            }
            return text_opacity;
        }

        float Object::getTextOpacity()
        {
            return text_opacity;
        }

        float Object::setBackgroundTextureOpacity(float alpha)
        {
            if(alpha >= 0 && alpha <= 1)
            {
                background_texture_opacity = alpha;
                auto opacity = static_cast<Uint8>(alpha * 255);
                if(background_texture != nullptr)
                {
                    background_texture->setAlphaMod(opacity);
                }
            }
            return background_texture_opacity;
        }

        float Object::getBackgroundTextureOpacity()
        {
            return background_texture_opacity;
        }
    }
}