#ifndef TURBO_OBJECT_H
#define TURBO_OBJECT_H

#include <map>
#include <functional>

#include <SDL_types.h>
#include <SDL_events.h>

#include "gui/gui_def.h"
#include "math/math.h"
#include "input/input.h"

namespace TURBO
{
    namespace GUI
    {
        class Object
        {
        protected:
            Object * parent;
            MATH::Rect geometry;
            std::map<std::string, std::function<void()>> callbacks;
            bool visible = false;
            bool mouse_over = false;
            bool mouse_clicked = false;

            void fireCallback(std::string callback);

        public:
            explicit Object(Object * parent);
            void pollEvent(SDL_Event &event);
            MATH::Rect setGeometry(MATH::Rect geometry);
            MATH::Rect getGeometry();
            bool isVisible();
            bool mouseOver();
            void onMouseOver(std::function<void()> callback);
            bool mouseClicked();
            Object & show();
        };
    }
}

#endif //TURBO_OBJECT_H
