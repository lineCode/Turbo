#ifndef TURBO_OBJECT_H
#define TURBO_OBJECT_H

#include <map>
#include <functional>
#include <algorithm>
#include <memory>

#include <SDL_types.h>
#include <SDL_events.h>

#include "gui/gui_def.h"
#include "gui/units.h"
#include "math/math.h"
#include "input/input.h"
#include "video/surface.h"
#include "video/texture.h"

namespace TURBO
{
    namespace GUI
    {
        class Object
        {
        private:
            static int objects;

        protected:
            int         id          = 0;
            Object      *parent     = nullptr;
            Object      *child      = nullptr;
            OBJECT_TYPE object_type = OBJECT_TYPE::OBJECT;

            bool mouse_on      = false;
            bool mouse_moving  = false;
            bool mouse_over    = false;
            bool mouse_out     = false;
            bool mouse_clicked = false;

            MATH::Point           position                   = MATH::Point();
            MATH::Rect            space                      = MATH::Rect();
            MATH::Rect            size                       = MATH::Rect();
            MATH::Rect            content                    = MATH::Rect();
            Uint8                 font_size                  = 12_pt;
            VIDEO::FONT_STYLE     font_style                 = VIDEO::FONT_STYLE::NORMAL;
            VIDEO::TEXT_ALIGNMENT text_alignment             = VIDEO::TEXT_ALIGNMENT::TOP_LEFT;
            VIDEO::TEXT_WRAPPING  text_wrapping              = VIDEO::TEXT_WRAPPING::BREAK;
            VIDEO::Texture        *background_texture        = nullptr;
            MATH::Rect            background_texture_rect    = MATH::Rect();
            VIDEO::Color          background_color           = VIDEO::WHITE;
            VIDEO::Color          text_color                 = VIDEO::BLACK;
            VIDEO::Color          border_color               = VIDEO::TRANSPARENT;
            MATH::Space           margin                     = MATH::Space();
            MATH::Space           padding                    = MATH::Space();
            bool                  visible                    = true;
            float                 opacity                    = 1.0;
            float                 text_opacity               = 1.0;
            float                 background_texture_opacity = 1.0;

            std::map<Uint8, std::function<void()>> callbacks;

            void fireCallback(Uint8 event);

        public:
            explicit Object(Object *parent);

            virtual ~Object();

            virtual void pollEvent(SDL_Event &event);

            void registerCallback(Uint8 event, std::function<void()> callback);

            OBJECT_TYPE getObjectType();

            OBJECT_TYPE setObjectType(OBJECT_TYPE type);

            bool mouseOver();

            bool mouseMoving();

            bool mouseOut();

            bool mouseClicked();

            int getId();

            Object *getParent();

            Object *setParent(Object *object);

            Object *getChild();

            virtual Object *setChild(Object *object);

            virtual void draw(VIDEO::Renderer *renderer);

            virtual Object *update();

            MATH::Point &setPosition(MATH::Point position);

            MATH::Point &getPosition();

            MATH::Rect &setSpace(MATH::Rect space);

            MATH::Rect &getSpace();

            MATH::Rect &setSize(MATH::Rect size);

            MATH::Rect &getSize();

            MATH::Rect &setContent(MATH::Rect content);

            MATH::Rect &getContent();

            Uint8 setFontSize(Uint8 size);

            Uint8 getFontSize();

            VIDEO::FONT_STYLE setFontStyle(VIDEO::FONT_STYLE style);

            VIDEO::FONT_STYLE getFontStyle();

            VIDEO::TEXT_ALIGNMENT setTextAlignment(VIDEO::TEXT_ALIGNMENT alignment);

            VIDEO::TEXT_ALIGNMENT getTextAlignment();

            VIDEO::TEXT_WRAPPING setTextWrapping(VIDEO::TEXT_WRAPPING wrapping);

            VIDEO::TEXT_WRAPPING getTextWrapping();

            VIDEO::Texture *getBackgroundTexture();

            VIDEO::Texture *setBackgroundTexture(std::string path, VIDEO::Renderer *renderer);

            MATH::Rect getBackgroundTextureRect();

            MATH::Rect setBackgroundTextureRect(MATH::Rect rect);

            VIDEO::Color getBackgroundColor();

            VIDEO::Color setBackgroundColor(VIDEO::Color color);

            VIDEO::Color getTextColor();

            VIDEO::Color setTextColor(VIDEO::Color color);

            VIDEO::Color getBorderColor();

            VIDEO::Color setBorderColor(VIDEO::Color color);

            MATH::Space getMargin();

            MATH::Space setMargin(MATH::Space margin);

            MATH::Space getPadding();

            MATH::Space setPadding(MATH::Space padding);

            bool isVisible();

            Object *hide();

            Object *show();

            Object *setVisibility(bool visible);

            float setOpacity(float alpha);

            float getOpacity();

            float setTextOpacity(float alpha);

            float getTextOpacity();

            float setBackgroundTextureOpacity(float alpha);

            float getBackgroundTextureOpacity();
        };
    }
}

#endif //TURBO_OBJECT_H
