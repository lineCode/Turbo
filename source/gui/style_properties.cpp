#include "gui/style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        StyleProperties::StyleProperties()
        {

        }

        StyleProperties::~StyleProperties()
        {
            delete background_texture;
        }

        Uint8 StyleProperties::setFontSize(Uint8 size)
        {
            font_size = size;
            return font_size;
        }

        Uint8 StyleProperties::getFontSize()
        {
            return font_size;
        }

        VIDEO::FONT_STYLE StyleProperties::setFontStyle(VIDEO::FONT_STYLE style)
        {
            font_style = style;
            return font_style;
        }

        VIDEO::FONT_STYLE StyleProperties::getFontStyle()
        {
            return font_style;
        }

        VIDEO::TEXT_WRAPPING StyleProperties::setTextWrapping(VIDEO::TEXT_WRAPPING wrapping)
        {
            text_wrapping = wrapping;
            return text_wrapping;
        }

        VIDEO::TEXT_WRAPPING StyleProperties::getTextWrapping()
        {
            return text_wrapping;
        }

        VIDEO::TEXT_ALIGNMENT StyleProperties::setTextAlignment(VIDEO::TEXT_ALIGNMENT alignment)
        {
            text_alignment = alignment;
            return text_alignment;
        }

        VIDEO::TEXT_ALIGNMENT StyleProperties::getTextAlignment()
        {
            return text_alignment;
        }

        VIDEO::Texture *StyleProperties::getBackgroundTexture()
        {
            return background_texture;
        }

        VIDEO::Texture *StyleProperties::setBackgroundTexture(const std::string path, VIDEO::Renderer *renderer)
        {
            VIDEO::Surface surface = VIDEO::Surface(path, renderer);
            background_texture = new VIDEO::Texture(renderer->getRenderer(), surface.getSurface());
            return background_texture;
        }

        VIDEO::Color StyleProperties::getBackgroundColor()
        {
            return background_color;
        }

        VIDEO::Color StyleProperties::setBackgroundColor(VIDEO::Color color)
        {
            background_color = color;
            return background_color;
        }

        VIDEO::Color StyleProperties::getFontColor()
        {
            return text_color;
        }

        VIDEO::Color StyleProperties::setFontColor(VIDEO::Color color)
        {
            text_color = color;
            return text_color;
        }

        VIDEO::Color StyleProperties::getBorderColor()
        {
            return border_color;
        }

        VIDEO::Color StyleProperties::setBorderColor(VIDEO::Color color)
        {
            border_color = color;
            return border_color;
        }
    }
}