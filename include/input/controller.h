#ifndef TURBO_CONTROLLER_H
#define TURBO_CONTROLLER_H

#include "input/input_def.h"

namespace TURBO
{
    namespace INPUT
    {
        class Controller
        {
        private:
            bool                    is_connected = false;
            Uint8                   controller_id = 0;
            SDL_GameController     *game_controller = nullptr;
            std::map<Uint8, bool>   controller_button_pressed;
            std::map<Uint8, bool>   controller_axis_moved;
            std::map<Uint8, Sint16> controller_axis_value;

        public:
            static std::map<Uint8, bool> controller_used;

            Controller();
            ~Controller();
            void            pollEvent(SDL_Event &event);
            bool            pressed(Uint8 controller_button);
            bool            axisMoved(Uint8 axis);
            Sint16          axisValue(Uint8 axis);
        };
    }
}

#endif //TURBO_CONTROLLER_H
