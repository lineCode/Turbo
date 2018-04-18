#include "input/keyboard.h"

namespace TURBO
{
    namespace INPUT
    {
        std::map<Sint32, bool> Keyboard::key_pressed = {};
        std::string Keyboard::text;
        Sint32 Keyboard::last_key = 0;
        Uint32 Keyboard::last_key_time = 0;

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

            last_key = event.key.keysym.sym;
            last_key_time = event.key.timestamp;
        }

        std::string Keyboard::getText()
        {
            return text;
        }

        std::string Keyboard::reduceText()
        {
            if(!text.empty())
            {
                text.pop_back();
            }
            return text;
        }

        void Keyboard::clearText()
        {
            text.clear();
        }

        bool Keyboard::pressed(SDL_Keycode sym)
        {
            return key_pressed[sym];
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2)
        {
            return key_pressed[sym1] && key_pressed[sym2];
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2)
        {
            return key_pressed[sym1] || key_pressed[sym2];
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3)
        {
            return key_pressed[sym1] && key_pressed[sym2] && key_pressed[sym3];
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3)
        {
            return key_pressed[sym1] || key_pressed[sym2] || key_pressed[sym3];
        }

        bool Keyboard::pressedAND(std::vector<SDL_Keycode> syms)
        {
            bool pressed = true;
            for(auto sym : syms)
            {
                pressed = pressed && key_pressed[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed;
        }

        bool Keyboard::pressedOR(std::vector<SDL_Keycode> syms)
        {
            bool pressed = false;
            for(auto sym : syms)
            {
                pressed = pressed || key_pressed[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed;
        }

        bool Keyboard::pressed(SDL_Keycode sym, SDL_Keymod mod)
        {
            return key_pressed[sym] && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keymod mod)
        {
            return key_pressed[sym1] && key_pressed[sym2] && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keymod mod)
        {
            return (key_pressed[sym1] || key_pressed[sym2]) && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3, SDL_Keymod mod)
        {
            return key_pressed[sym1] && key_pressed[sym2] && key_pressed[sym3] && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3, SDL_Keymod mod)
        {
            return (key_pressed[sym1] || key_pressed[sym2] || key_pressed[sym3]) && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedAND(std::vector<SDL_Keycode> syms, SDL_Keymod mod)
        {
            bool pressed = true;
            for(auto sym : syms)
            {
                pressed = pressed && key_pressed[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedOR(std::vector<SDL_Keycode> syms, SDL_Keymod mod)
        {
            bool pressed = false;
            for(auto sym : syms)
            {
                pressed = pressed || key_pressed[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed && SDL_GetModState() & mod;
        }
    }
}