#ifndef TURBO_STYLE_PROPERTIES_H
#define TURBO_STYLE_PROPERTIES_H

#include "gui/gui_def.h"

namespace TURBO
{
    namespace GUI
    {
        class Background
        {
        public:
            VIDEO::Color background_color;

            explicit Background(VIDEO::Color color);
        };

        class StyleProperties
        {
        protected:
            Background background;
            VIDEO::Color text_color;

        public:
            StyleProperties();
            Background getBackground();
            Background setBackground(Background background);
        };
    }
}

#endif //TURBO_STYLE_PROPERTIES_H
