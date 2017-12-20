#ifndef TURBO_OBJECT_H
#define TURBO_OBJECT_H

#include <map>
#include <functional>

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
            bool mouse_over;
            bool mouse_clicked;

            void fireCallback(Uint8 event);

        public:
            explicit Object(Object *parent);
            ~Object();
            void pollEvent(SDL_Event &event);
            void registerCallback(Uint8 event, std::function<void()> &callback);
            MATH::Rect &setGeometry(MATH::Rect geometry);
            MATH::Rect &getGeometry();
            MATH::Rect &setSize(MATH::Rect size);
            MATH::Rect &getSize();
            OBJECT_TYPE getType();
            bool isVisible();
            bool mouseOver();
            bool mouseClicked();
            Object *getParent();
            Object *setParent(Object *object);
            Object *getChild();
            Object *setChild(Object *object);
            Object *hide();
            Object *show();
            virtual Object *update();
        };
    }
}

#endif //TURBO_OBJECT_H
