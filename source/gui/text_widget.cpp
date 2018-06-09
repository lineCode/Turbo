#include "gui/text_widget.h"

namespace TURBO
{
    namespace GUI
    {
        TextWidget::TextWidget(Object *parent, const std::string text)
            : Widget(parent), text(text), text_texture(nullptr), text_rect()
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
                renderer->setTextColor(text_color);
                delete text_texture;
                text_texture = renderer->createUTF8Text(text, font_size, size.w, size.h);
                text_rect = MATH::Rect(space.x, space.y, text_texture->getWidth(), text_texture->getHeight());

                if((text_alignment & 0x1) == 1) // Left alignment
                {

                }
                else if((text_alignment & 0x2) == 2) // Center alignment
                {
                    Sint32 align_space = (space.w - text_rect.w) / 2;
                    text_rect.add(align_space, 0, 0, 0);
                }
                else if((text_alignment & 0x4) == 4) // Right alignment
                {
                    Sint32 align_space = space.w - text_rect.w;
                    text_rect.add(align_space, 0, 0, 0);
                }
            }
            Object::draw(renderer);
            renderer->drawTexture(text_texture, text_rect);
        }
    }
}