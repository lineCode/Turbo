#ifndef TURBO_KEYBOARD_H
#define TURBO_KEYBOARD_H

#include <vector>

#include "input/input_def.h"

namespace TURBO
{
    namespace INPUT
    {
        class Keyboard
        {
        private:
            static std::map<Sint32, bool> key_pressed;
            static std::string text;
            static Sint32 last_key;
            static Uint32 last_key_time;

        public:
            static void pollEvent(SDL_Event &event);
            static std::string getText();
            static std::string reduceText();
            static void clearText();
            static bool pressed(SDL_Keycode sym);
            static bool pressedAND(SDL_Keycode sym1, SDL_Keycode sym2);
            static bool pressedOR(SDL_Keycode sym1, SDL_Keycode sym2);
            static bool pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3);
            static bool pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3);
            static bool pressedAND(std::vector<SDL_Keycode> syms);
            static bool pressedOR(std::vector<SDL_Keycode> syms);
            static bool pressed(SDL_Keycode sym, SDL_Keymod mod);
            static bool pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keymod mod);
            static bool pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keymod mod);
            static bool pressedAND(std::vector<SDL_Keycode> syms, SDL_Keymod mod);
            static bool pressedOR(std::vector<SDL_Keycode> syms, SDL_Keymod mod);
            static bool pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3, SDL_Keymod mod);
            static bool pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3, SDL_Keymod mod);
        };
    }
}

#endif //TURBO_KEYBOARD_H
