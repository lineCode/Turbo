#include "gui/text_widget.h"

namespace TURBO
{
    namespace GUI
    {
        TextWidget::TextWidget(Object *parent, const std::string text)
            : Widget(parent), text(text), text_texture(nullptr)
        {
            object_type = OBJECT_TYPE::TEXT_WIDGET;
        }

        TextWidget::~TextWidget()
        {
            delete text_texture;
        }

        std::string TextWidget::getText() const
        {
            return text;
        }

        std::string TextWidget::setText(const std::string text)
        {
            this->text = text;
            return this->text;
        }

        void TextWidget::draw(VIDEO::Renderer *renderer)
        {
            if(text_texture == nullptr)
            {
                int text_size = renderer->getFont()->getUTF8TextSize(text).w;
                if(text_size > size.w)
                {
                    //TODO get roughly the size of the optimal font size
                    Uint8 ideal_size = 12;//static_cast<Uint8>(text_size - size.w);
                    text_texture = renderer->createUTF8Text(text, ideal_size, size.w, size.h);
                }
                else
                {
                    text_texture = renderer->createUTF8Text(text, size.w, size.h);
                }
            }
            Object::draw(renderer);
            renderer->drawTexture(text_texture, size);
        }
    }
}