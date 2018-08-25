#ifndef TURBO_MOUSE_H
#define TURBO_MOUSE_H

#include "input/input_def.h"
#include "math/point.h"

namespace TURBO
{
    namespace INPUT
    {
        class Mouse
        {
        private:
            static MATH::Point pos;
            static MATH::Point last_pos;
            static MATH::Point global_pos;
            static std::map<Uint8, bool> mouse_button_pressed;
            static bool mouse_pressed;
            static bool mouse_moved;
            static bool mouse_wheel_moved;

        public:
            static void pollEvent(SDL_Event *event);
            static MATH::Point getPosition();
            static MATH::Point getLastPosition();
            static MATH::Point getGlobalPosition();
            static bool pressed(Uint8 mouse_button);
            static bool pressed();
            static bool moved();
            static bool wheelMoved();
        };
    }
}

#endif //TURBO_MOUSE_H
