#ifndef TURBO_OBJECT_H
#define TURBO_OBJECT_H

#include <map>
#include <functional>
#include <algorithm>

#include <SDL_types.h>
#include <SDL_events.h>

#include "gui/gui_def.h"
#include "math/math.h"
#include "input/input.h"
#include "style_properties.h"

namespace TURBO
{
    namespace GUI
    {
        class Object : public StyleProperties
        {
        protected:
            Object *parent;
            Object *child;
            MATH::Rect geometry;
            MATH::Rect size;
            std::map<Uint8, std::function<void()>> callbacks;
            OBJECT_TYPE object_type;
            bool visible;
            float opacity;
            bool mouse_on;
            bool mouse_over;
            bool mouse_out;
            bool mouse_clicked;

            void fireCallback(Uint8 event);

        public:
            explicit Object(Object *parent);
            virtual ~Object();
            void pollEvent(SDL_Event &event);
            void registerCallback(Uint8 event, std::function<void()> callback);
            MATH::Rect &setGeometry(MATH::Rect geometry);
            MATH::Rect &getGeometry();
            MATH::Rect &setSize(MATH::Rect size);
            MATH::Rect &getSize();
            OBJECT_TYPE getObjectType();
            OBJECT_TYPE setObjectType(OBJECT_TYPE type);
            bool isVisible();
            bool mouseOver();
            bool mouseOut();
            bool mouseClicked();
            Object *getParent();
            Object *setParent(Object *object);
            Object *getChild();
            Object *setChild(Object *object);
            Object *hide();
            Object *show();
            Object *setVisibility(bool visible);
            float setOpacity(float alpha);
            float getOpacity();
            virtual void draw(VIDEO::Renderer * renderer);
            virtual Object *update();
        };
    }
}

#endif //TURBO_OBJECT_H
