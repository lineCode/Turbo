#include "gui/style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        Background::Background(VIDEO::Color color)
            : background_color(color)
        {

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