#include "gui/object_style.h"

namespace TURBO
{
    namespace GUI
    {
        Space::Space()
            : top(0), right(0), bottom(0), left(0)
        {

        }

        Space::Space(Uint32 top, Uint32 right, Uint32 bottom, Uint32 left)
            : top(top), right(right), bottom(bottom), left(left)
        {

        }

        void Space::setSpace(Uint32 top, Uint32 right, Uint32 bottom, Uint32 left)
        {
            this->top    = top;
            this->right  = right;
            this->bottom = bottom;
            this->left   = left;
        }

        ObjectStyle::ObjectStyle()
            : margin(),
              padding()
        {

        }

        ObjectStyle::~ObjectStyle()
        {
            delete background_texture;
        }

        MATH::Point &ObjectStyle::setPosition(MATH::Point position)
        {
            this->position = position;
            return this->position;
        }

        MATH::Point &ObjectStyle::getPosition()
        {
            return position;
        }

        MATH::Rect &ObjectStyle::setSpace(MATH::Rect space)
        {
            this->space = space;
            return this->space;
        }

        MATH::Rect &ObjectStyle::getSpace()
        {
            return space;
        }

        MATH::Rect &ObjectStyle::setSize(MATH::Rect size)
        {
            if(size <= space)
            {
                this->size = size;
            }
            return this->size;
        }

        MATH::Rect &ObjectStyle::getSize()
        {
            return size;
        }

        MATH::Rect &ObjectStyle::setContent(MATH::Rect content)
        {
            if(content <= size)
            {
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

        MATH::Rect &ObjectStyle::getContent()
        {
            return this->content;
        }

        Uint8 ObjectStyle::setFontSize(Uint8 size)
        {
            font_size = size;
            return font_size;
        }

        Uint8 ObjectStyle::getFontSize()
        {
            return font_size;
        }

        VIDEO::FONT_STYLE ObjectStyle::setFontStyle(VIDEO::FONT_STYLE style)
        {
            font_style = style;
            return font_style;
        }

        VIDEO::FONT_STYLE ObjectStyle::getFontStyle()
        {
            return font_style;
        }

        VIDEO::TEXT_WRAPPING ObjectStyle::setTextWrapping(VIDEO::TEXT_WRAPPING wrapping)
        {
            text_wrapping = wrapping;
            return text_wrapping;
        }

        VIDEO::TEXT_WRAPPING ObjectStyle::getTextWrapping()
        {
            return text_wrapping;
        }

        VIDEO::TEXT_ALIGNMENT ObjectStyle::setTextAlignment(VIDEO::TEXT_ALIGNMENT alignment)
        {
            text_alignment = alignment;
            return text_alignment;
        }

        VIDEO::TEXT_ALIGNMENT ObjectStyle::getTextAlignment()
        {
            return text_alignment;
        }

        VIDEO::Texture *ObjectStyle::getBackgroundTexture()
        {
            return background_texture;
        }

        VIDEO::Texture *ObjectStyle::setBackgroundTexture(const std::string path, VIDEO::Renderer *renderer)
        {
            VIDEO::Surface surface = VIDEO::Surface(path, renderer);
            background_texture = new VIDEO::Texture(renderer->getRenderer(), surface.getSurface());

            if(background_texture != nullptr)
            {
                SDL_Rect   tex = background_texture->getSize();
                MATH::Rect tex_rect(0, 0, tex.w, tex.h);

                Sint32 max_width  = std::max(tex.w, std::max(space.w, 1));
                Sint32 max_height = std::max(tex.h, std::max(space.h, 1));

                float width_factor  = tex.w / std::max(space.w, 1);
                float height_factor = tex.h / std::max(space.h, 1);

                float factor = (width_factor > height_factor) ? width_factor : height_factor;

                background_texture_rect = MATH::Rect(content.x, content.y,
                                                     static_cast<Sint32>(tex_rect.w / factor),
                                                     static_cast<Sint32>(tex_rect.h / factor));
            }
            return background_texture;
        }

        VIDEO::Color ObjectStyle::getBackgroundColor()
        {
            return background_color;
        }

        VIDEO::Color ObjectStyle::setBackgroundColor(VIDEO::Color color)
        {
            background_color = color;
            return background_color;
        }

        VIDEO::Color ObjectStyle::getFontColor()
        {
            return text_color;
        }

        VIDEO::Color ObjectStyle::setFontColor(VIDEO::Color color)
        {
            text_color = color;
            return text_color;
        }

        VIDEO::Color ObjectStyle::getBorderColor()
        {
            return border_color;
        }

        VIDEO::Color ObjectStyle::setBorderColor(VIDEO::Color color)
        {
            border_color = color;
            return border_color;
        }
    }
}