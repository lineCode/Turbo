#include "gui/style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        Color::Color(float r, float g, float b, float a)
            : r(r), g(g), b(b), a(a)
        {

        }

        Background::Background(Color color)
            : background_color(color)
        {

        }

        StyleProperties::StyleProperties()
            : background({1.0, 1.0, 1.0, 1.0}),
              text_color({0.0, 0.0, 0.0, 1.0})
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