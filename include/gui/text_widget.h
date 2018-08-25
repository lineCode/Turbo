#ifndef TURBO_TEXT_WIDGET_H
#define TURBO_TEXT_WIDGET_H

#include "gui/widget.h"

namespace TURBO
{
    namespace GUI
    {
        class TextWidget
            : public Widget
        {
        protected:
            std::string    text;
            VIDEO::Texture *text_texture = nullptr;
            MATH::Rect     text_rect     = MATH::Rect();

        public:
            TextWidget(std::string text);

            TextWidget(Object *parent, std::string text);

            ~TextWidget() override;

            std::string getText() const;

            std::string setText(std::string text);

            void draw(VIDEO::Renderer *renderer) override;
        };
    }
}

#endif //TURBO_TEXT_WIDGET_H
