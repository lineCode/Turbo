#ifndef TURBO_KEYBOARD_H
#define TURBO_KEYBOARD_H

#include <vector>
#include <set>
#include <iostream>

#include "input/input_def.h"
#include "system/time.h"

namespace TURBO
{
    namespace INPUT
    {
        class KeyCombination;

        class Key
        {
        private:
            Sint64 code = 0;

        public:
            explicit Key(SDL_Keycode code);
            explicit Key(Sint64 code);
            bool operator<(const Key & other) const;
            KeyCombination operator&(Key other);
            KeyCombination operator|(Key other);
            Sint64 setCode(Sint64 code);
            Sint64 setCode(SDL_Keycode code);
            Sint64 setCode(Key key);
            Sint64 getCode() const;
        };

        class KeyMod
        {
        private:
            Sint64 code = 0;

        public:
            explicit KeyMod(SDL_Keymod mod);
            explicit KeyMod(KEYMOD mod);
            explicit KeyMod(Key & code);
            Sint64 getMod();
            Key getKey();
        };

        class KeyCombination
        {
        private:
            std::set<std::set<Key>> combs;

        public:
            explicit KeyCombination(SDL_Keycode keycode);
            explicit KeyCombination(SDL_Keymod keymod);
            explicit KeyCombination(Key key);
            explicit KeyCombination(KeyMod mod);
            std::set<std::set<Key>> getComb();
            KeyCombination &operator&(SDL_Keycode keycode);
            KeyCombination &operator&=(SDL_Keycode keycode);
            KeyCombination &operator&(SDL_Keymod keymod);
            KeyCombination &operator&=(SDL_Keymod keymod);
            KeyCombination &operator&(Key key);
            KeyCombination &operator&=(Key key);
            KeyCombination &operator&(KeyMod mod);
            KeyCombination &operator&=(KeyMod mod);
            KeyCombination &operator&(KeyCombination combination);
            KeyCombination &operator&=(KeyCombination combination);
            KeyCombination &operator|(SDL_Keycode keycode);
            KeyCombination &operator|=(SDL_Keycode keycode);
            KeyCombination &operator|(SDL_Keymod keymod);
            KeyCombination &operator|=(SDL_Keymod keymod);
            KeyCombination &operator|(Key key);
            KeyCombination &operator|=(Key key);
            KeyCombination &operator|(KeyMod mod);
            KeyCombination &operator|=(KeyMod mod);
            KeyCombination &operator|(KeyCombination combination);
            KeyCombination &operator|=(KeyCombination combination);
        };

        class Keyboard
        {
        private:
            static std::map<Sint32, KEY_STATE> key;
            static std::map<Sint32, Uint32> timestamp;
            static std::string text;

        public:
            static void pollEvent(SDL_Event &event);
            static std::string getText();
            static std::string reduceText();
            static void clearText();
            static bool pressed(KeyCombination comb);
            static bool pressed(SDL_Keycode sym);
            static bool pressed(Key key);
            static bool down(KeyCombination comb);
            static bool down(SDL_Keycode sym);
            static bool released(SDL_Keycode sym);
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
