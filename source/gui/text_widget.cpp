#include "gui/text_widget.h"

namespace TURBO
{
    namespace GUI
    {
        TextWidget::TextWidget(Object *parent, const std::string text)
            : Object(parent), text(text), text_texture(nullptr)
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
                text_texture = renderer->createUTF8Text(text, size.w, size.h);
            }
            Object::draw(renderer);
            renderer->drawTexture(text_texture->getTexture(), size.x, size.y);
        }
    }
}