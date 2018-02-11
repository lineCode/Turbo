#ifndef TURBO_STYLE_PROPERTIES_H
#define TURBO_STYLE_PROPERTIES_H

#include "gui/gui_def.h"
#include "video/surface.h"

namespace TURBO
{
    namespace GUI
    {
        class StyleProperties
        {
        protected:
            VIDEO::Color background_color;
            VIDEO::Texture *background_texture;
            VIDEO::Color text_color;
            VIDEO::Color border_color;

        public:
            StyleProperties();
            virtual ~StyleProperties();
            VIDEO::Texture *getBackgroundTexture();
            VIDEO::Texture *setBackgroundTexture(std::string path, VIDEO::Renderer *renderer);
            VIDEO::Color getBackgroundColor();
            VIDEO::Color setBackgroundColor(VIDEO::Color color);
            VIDEO::Color getFontColor();
            VIDEO::Color setFontColor(VIDEO::Color color);
            VIDEO::Color getBorderColor();
            VIDEO::Color setBorderColor(VIDEO::Color color);
        };
    }
}

#endif //TURBO_STYLE_PROPERTIES_H
