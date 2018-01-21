#include "gui/style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        Background::Background(VIDEO::Color color)
            : background_color(color)
        {

        }

        Background::Background(VIDEO::Texture *texture)
            : background_color({0x00, 0x00, 0x00, 0xFF}), background_texture(texture)
        {

        }

        Background::Background(std::string path, VIDEO::Renderer *renderer)
            : background_color({0x00, 0x00, 0x00, 0xFF})
        {
            background_texture = new VIDEO::Texture(renderer->getRenderer(), nullptr);
        }

        StyleProperties::StyleProperties()
            : background({0xFF, 0xFF, 0xFF, 0xFF}),
              text_color({0x00, 0x00, 0x00, 0xFF})
        {

        }

        Background StyleProperties::getBackground()
        {
            return background;
        }

        Background StyleProperties::setBackground(Background background)
        {
            this->background = background;
            return this->background;
        }
    }
}