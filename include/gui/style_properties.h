#ifndef TURBO_STYLE_PROPERTIES_H
#define TURBO_STYLE_PROPERTIES_H

#include "gui/gui_def.h"
#include "gui/units.h"
#include "video/surface.h"

namespace TURBO
{
    namespace GUI
    {
        class StyleProperties
        {
        protected:
            Uint8                 font_size           = 14_px;
            VIDEO::FONT_STYLE     font_style          = VIDEO::FONT_STYLE::NORMAL;
            VIDEO::TEXT_ALIGNMENT text_alignment      = VIDEO::TEXT_ALIGNMENT::TOP_LEFT;
            VIDEO::TEXT_WRAPPING  text_wrapping       = VIDEO::TEXT_WRAPPING::BREAK;
            VIDEO::Texture        *background_texture = nullptr;
            VIDEO::Color          background_color    = VIDEO::Color(0xFF, 0xFF, 0xFF, 0xFF);
            VIDEO::Color          text_color          = VIDEO::Color(0x00, 0x00, 0x00, 0xFF);
            VIDEO::Color          border_color        = VIDEO::Color(0x00, 0x00, 0x00, 0x00);

        public:
            StyleProperties();

            virtual ~StyleProperties();

            virtual Uint8 setFontSize(Uint8 size);

            virtual Uint8 getFontSize();

            virtual VIDEO::FONT_STYLE setFontStyle(VIDEO::FONT_STYLE style);

            virtual VIDEO::FONT_STYLE getFontStyle();

            virtual VIDEO::TEXT_ALIGNMENT setTextAlignment(VIDEO::TEXT_ALIGNMENT alignment);

            virtual VIDEO::TEXT_ALIGNMENT getTextAlignment();

            virtual VIDEO::TEXT_WRAPPING setTextWrapping(VIDEO::TEXT_WRAPPING wrapping);

            virtual VIDEO::TEXT_WRAPPING getTextWrapping();

            virtual VIDEO::Texture *getBackgroundTexture();

            virtual VIDEO::Texture *setBackgroundTexture(std::string path, VIDEO::Renderer *renderer);

            virtual VIDEO::Color getBackgroundColor();

            virtual VIDEO::Color setBackgroundColor(VIDEO::Color color);

            virtual VIDEO::Color getFontColor();

            virtual VIDEO::Color setFontColor(VIDEO::Color color);

            virtual VIDEO::Color getBorderColor();

            virtual VIDEO::Color setBorderColor(VIDEO::Color color);
        };
    }
}

#endif //TURBO_STYLE_PROPERTIES_H
