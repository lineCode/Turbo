#ifndef TURBO_TEXT_WIDGET_H
#define TURBO_TEXT_WIDGET_H

#include "video/font.h"

#include "gui/widget.h"

namespace TURBO
{
    namespace GUI
    {
        class TextWidget : public Widget
        {
        protected:
            std::string text;
            VIDEO::Texture *text_texture;
            MATH::Rect text_rect;

        public:
            TextWidget(Object *parent, std::string text);
            ~TextWidget() override;
            std::string getText() const;
            std::string setText(std::string text);
            void draw(VIDEO::Renderer *renderer) override;
        };
    }
}

#endif //TURBO_TEXT_WIDGET_H
