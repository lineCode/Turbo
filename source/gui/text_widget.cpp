#include <utility>

#include "gui/text_widget.h"

namespace TURBO
{
    namespace GUI
    {
        TextWidget::TextWidget(std::string text)
        : Widget(nullptr), text(std::move(text))
        {

        }

        TextWidget::TextWidget(Object *parent, std::string text)
            : Widget(parent), text(std::move(text))
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
                auto pt_size = static_cast<Uint8>(font_size * PT_TO_PX);
                text_texture = renderer->createUTF8Text(text, pt_size, size.w, size.h, font_style, text_wrapping);
                text_rect = MATH::Rect(space.x, space.y, text_texture->getWidth(), text_texture->getHeight());

                if((text_alignment & 0x1) == 0x1) // Left alignment
                {
                    // default
                }
                else if((text_alignment & 0x2) == 0x2) // Center alignment
                {
                    Sint32 align_space = (size.w - text_rect.w) / 2;
                    text_rect.add(align_space, 0, 0, 0);
                }
                else if((text_alignment & 0x4) == 0x4) // Right alignment
                {
                    Sint32 align_space = size.w - text_rect.w;
                    text_rect.add(align_space, 0, 0, 0);
                }

                if((text_alignment & 0x10) == 0x10) // Top alignment
                {
                    // default
                }
                else if((text_alignment & 0x20) == 0x20) // Middle alignment
                {
                    Sint32 align_space = (size.h - text_rect.h) / 2;
                    text_rect.add(0, align_space, 0, 0);
                }
                else if((text_alignment & 0x40) == 0x40) // Bottom alignment
                {
                    Sint32 align_space = size.h - text_rect.h;
                    text_rect.add(0, align_space, 0, 0);
                }
            }
            Object::draw(renderer);
            renderer->drawTexture(text_texture, text_rect);
        }
    }
}