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
            this->top = top;
            this->right = right;
            this->bottom = bottom;
            this->left = left;
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