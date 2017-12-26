#ifndef TURBO_STYLE_PROPERTIES_H
#define TURBO_STYLE_PROPERTIES_H

#include "gui/gui_def.h"

namespace TURBO
{
    namespace GUI
    {
        class Color
        {
        public:
            float r;
            float g;
            float b;
            float a;

            Color(float r, float g, float b, float a);
        };

        class Background
        {
        public:
            Color background_color;

            explicit Background(Color color);
        };

        class StyleProperties
        {
        protected:
            Background background;
            Color text_color;

        public:
            StyleProperties();
            Background getBackground();
            Background setBackground(Background background);
        };
    }
}

#endif //TURBO_STYLE_PROPERTIES_H
