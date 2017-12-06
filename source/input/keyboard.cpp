#include "input/keyboard.h"

namespace TURBO
{
    namespace INPUT
    {
        std::map<Sint32, bool> Keyboard::key_pressed = {};

        void Keyboard::pollEvent(SDL_Event &event)
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(!key_pressed[event.key.keysym.sym])
                {
                    key_pressed[event.key.keysym.sym] = true;
                }
            }
            else if(event.type == SDL_KEYUP)
            {
                if(key_pressed[event.key.keysym.sym])
                {
                    key_pressed[event.key.keysym.sym] = false;
                }
            }
        }

        bool Keyboard::pressed(SDL_Keycode sym)
        {
            return key_pressed[sym];
        }

        bool Keyboard::pressed(SDL_Keycode sym, SDL_Keymod mod)
        {
            return key_pressed[sym] && SDL_GetModState() & mod;
        }
    }
}