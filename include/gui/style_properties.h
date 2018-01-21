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
            VIDEO::Texture * background_texture;

            explicit Background(VIDEO::Color color);
            explicit Background(VIDEO::Texture * texture);
            explicit Background(std::string path, VIDEO::Renderer *renderer);
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
