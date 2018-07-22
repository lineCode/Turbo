#ifndef TURBO_OBJECT_H
#define TURBO_OBJECT_H

#include <map>
#include <functional>
#include <algorithm>
#include <memory>

#include <SDL_types.h>
#include <SDL_events.h>

#include "gui/gui_def.h"
#include "math/math.h"
#include "input/input.h"
#include "gui/object_style.h"

namespace TURBO
{
    namespace GUI
    {
        class Object
            : public ObjectStyle
        {
        private:
            static int objects;

        protected:
            int         id            = 0;
            Object      *parent       = nullptr;
            Object      *child        = nullptr;
            MATH::Point position      = MATH::Point();
            MATH::Rect  space         = MATH::Rect();
            MATH::Rect  size          = MATH::Rect();
            MATH::Rect  content       = MATH::Rect();
            OBJECT_TYPE object_type   = OBJECT_TYPE::OBJECT;
            float       opacity       = 1.0;
            bool        visible       = false;
            bool        mouse_on      = false;
            bool        mouse_over    = false;
            bool        mouse_out     = false;
            bool        mouse_clicked = false;

            std::map<Uint8, std::function<void()>> callbacks;

            void fireCallback(Uint8 event);

        public:
            explicit Object(Object *parent);

            ~Object() override;

            virtual void pollEvent(SDL_Event &event);

            void registerCallback(Uint8 event, std::function<void()> callback);

            MATH::Point &setPosition(MATH::Point position);

            MATH::Point &getPosition();

            MATH::Rect &setSpace(MATH::Rect space);

            MATH::Rect &getSpace();

            MATH::Rect &setSize(MATH::Rect size);

            MATH::Rect &getSize();

            MATH::Rect &setContent(MATH::Rect content);

            MATH::Rect &getContent();

            OBJECT_TYPE getObjectType();

            OBJECT_TYPE setObjectType(OBJECT_TYPE type);

            bool isVisible();

            bool mouseOver();

            bool mouseOut();

            bool mouseClicked();

            int getId();

            Object *getParent();

            Object *setParent(Object *object);

            Object *getChild();

            virtual Object *setChild(Object *object);

            Object *hide();

            Object *show();

            Object *setVisibility(bool visible);

            float setOpacity(float alpha);

            float getOpacity();

            virtual void draw(VIDEO::Renderer *renderer);

            virtual Object *update();
        };
    }
}

#endif //TURBO_OBJECT_H
