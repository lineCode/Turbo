#include "gui/style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        Background::Background(Color color)
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
    }
}