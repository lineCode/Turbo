#include "input/controller.h"

namespace TURBO
{
    namespace INPUT
    {
        std::map<Uint8, bool> Controller::controller_used = {};

        Controller::Controller()
        {
            for(Uint8 controller = 0; controller < std::min(static_cast<Uint8>(SDL_NumJoysticks()), MAX_CONTROLLERS); ++controller)
            {
                if(!Controller::controller_used[controller])
                {
                    game_controller = SDL_GameControllerOpen(controller);
                    if(game_controller != nullptr)
                    {
                        is_connected = true;
                        controller_id = controller;
                        Controller::controller_used[controller] = true;
                        break;
                    }
                }
            }
        }

        Controller::~Controller()
        {
            if(is_connected)
            {
                SDL_GameControllerClose(game_controller);
                Controller::controller_used[controller_id] = false;
            }
        }

        void Controller::pollEvent(SDL_Event &event)
        {
            if(event.cdevice.which == controller_id)
            {
                for(auto axis : controller_axis_moved)
                {
                    controller_axis_moved[axis.first] = false;
                }

                if(event.type == SDL_CONTROLLERBUTTONDOWN)
                {
                    if(!controller_button_pressed[event.cbutton.button])
                    {
                        controller_button_pressed[event.cbutton.button] = true;
                    }
                }
                else if(event.type == SDL_CONTROLLERBUTTONUP)
                {
                    if(!controller_button_pressed[event.cbutton.button])
                    {
                        controller_button_pressed[event.cbutton.button] = true;
                    }
                }
                else if(event.type == SDL_CONTROLLERAXISMOTION)
                {
                    controller_axis_moved[event.caxis.axis] = true;
                    controller_axis_value[event.caxis.axis] = event.caxis.value;
                }
            }
        }

        bool Controller::pressed(Uint8 controller_button)
        {
            return controller_button_pressed[controller_button];
        }

        bool Controller::axisMoved(Uint8 axis)
        {
            return controller_axis_moved[axis];
        }

        Sint16 Controller::axisValue(Uint8 axis)
        {
            return controller_axis_value[axis];
        }
    }
}