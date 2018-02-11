#include "input/mouse.h"

namespace TURBO
{
    namespace INPUT
    {
        MATH::Point Mouse::pos = MATH::Point(0, 0);
        MATH::Point Mouse::last_pos = MATH::Point(0, 0);
        MATH::Point Mouse::global_pos = MATH::Point(0, 0);
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
            }
            else if(event.type == SDL_MOUSEWHEEL)
            {
                mouse_wheel_moved = true;
            }
        }

        MATH::Point Mouse::getPosition()
        {
            SDL_GetMouseState(&pos.x, &pos.y);
            return pos;
        }

        MATH::Point Mouse::getLastPosition()
        {
            SDL_GetRelativeMouseState(&last_pos.x, &last_pos.y);
            return last_pos;
        }

        MATH::Point Mouse::getGlobalPosition()
        {
            SDL_GetGlobalMouseState(&global_pos.x, &global_pos.y);
            return global_pos;
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