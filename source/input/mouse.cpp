#include "input/mouse.h"

namespace TURBO
{
    namespace INPUT
    {
        MATH::Point Mouse::pos = MATH::Point(0, 0);
        std::map<Uint8, bool> Mouse::mouse_button_pressed = {};
        bool Mouse::mouse_pressed = false;
        bool Mouse::mouse_moved = false;
        bool Mouse::mouse_wheel_moved = false;

        void Mouse::pollEvent(SDL_Event &event)
        {
            mouse_moved = false;
            mouse_wheel_moved = false;

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouse_pressed = true;
                if(!mouse_button_pressed[event.button.button])
                {
                    mouse_button_pressed[event.button.button] = true;
                }
            }
            else if(event.type == SDL_MOUSEBUTTONUP)
            {
                mouse_pressed = false;
                if(mouse_button_pressed[event.button.button])
                {
                    mouse_button_pressed[event.button.button] = false;
                }
            }
            else if(event.type == SDL_MOUSEMOTION)
            {
                mouse_moved = true;
                pos = MATH::Point(event.motion.x, event.motion.y);
            }
            else if(event.type == SDL_MOUSEWHEEL)
            {
                mouse_wheel_moved = true;
            }
        }

        MATH::Point Mouse::getPosition()
        {
            return pos;
        }

        bool Mouse::pressed(Uint8 mouse_button)
        {
            return mouse_button_pressed[mouse_button];
        }

        bool Mouse::pressed()
        {
            return mouse_pressed;
        }

        bool Mouse::moved()
        {
            return mouse_moved;
        }

        bool Mouse::wheelMoved()
        {
            return mouse_wheel_moved;
        }
    }
}