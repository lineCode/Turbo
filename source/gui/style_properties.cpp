#include "gui/style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        StyleProperties::StyleProperties()
            : background_texture(nullptr),
              background_color({0xFF, 0xFF, 0xFF, 0xFF}),
              text_color({0x00, 0x00, 0x00, 0xFF}),
              border_color({0x00, 0x00, 0x00, 0x00})
        {

        }

        StyleProperties::~StyleProperties()
        {
            delete background_texture;
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