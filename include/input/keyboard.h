#ifndef TURBO_KEYBOARD_H
#define TURBO_KEYBOARD_H

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

        public:
            static void pollEvent(SDL_Event &event);
            static std::string getText();
            static std::string reduceText();
            static void clearText();
            static bool pressed(SDL_Keycode sym);
            static bool pressed(SDL_Keycode sym, SDL_Keymod mod);
        };
    }
}

#endif //TURBO_KEYBOARD_H
