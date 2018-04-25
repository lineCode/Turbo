#include "input/keyboard.h"

namespace TURBO
{
    namespace INPUT
    {
        Key::Key(SDL_Keycode code)
            : code(code)
        {

        }

        Key::Key(Sint64 code)
            : code(code)
        {

        }

        bool Key::operator<(const Key &other) const
        {
            return code < other.code;
        }

        Sint64 Key::setCode(Sint64 code)
        {
            this->code = code;
            return this->code;
        }

        Sint64 Key::setCode(SDL_Keycode code)
        {
            this->code = code;
            return this->code;
        }

        Sint64 Key::setCode(Key key)
        {
            code = key.getCode();
            return code;
        }

        Sint64 Key::getCode()
        {
            return code;
        }

        KeyMod::KeyMod(KEYMOD mod)
            : code(mod)
        {

        }

        KeyMod::KeyMod(Key &code)
            : code(code.getCode())
        {

        }

        KeyMod::KeyMod(KeyMod &mod)
            : code(mod.getMod())
        {

        }

        Sint64 KeyMod::getMod()
        {
            return code;
        }

        Key KeyMod::getKey()
        {
            return Key{code};
        }

        KeyCombination::KeyCombination(Key key)
        {
            keys.insert(key);
        }

        KeyCombination::KeyCombination(KeyMod mod)
        {
            keys.insert(mod.getKey());
        }

        KeyCombination::KeyCombination(KeyCombination &combination)
        {
            setKeys(combination.getKeys());
        }

        KeyCombination::KeyCombination(Key key1, Key key2)
        {
            addKey(key1);
            addKey(key2);
        }

        KeyCombination::KeyCombination(std::set<Key> & keys)
        {
            addKeys(keys);
        }

        std::set<Key> KeyCombination::setKeys(std::set<Key> keys)
        {
            this->keys = keys;
            return keys;
        }

        std::set<Key> KeyCombination::addKey(Key key)
        {
            keys.insert(key);
            return keys;
        }

        std::set<Key> KeyCombination::addKeys(std::set<Key> keys)
        {
            keys.insert(keys.begin(), keys.end());
            return this->keys;
        }

        std::set<Key> KeyCombination::getKeys()
        {
            return keys;
        }

        KeyCombination &KeyCombination::operator&(Key key)
        {
            return *this;
        }

        KeyCombination &KeyCombination::operator&(KeyMod mod)
        {
            return *this;
        }

        KeyCombination &KeyCombination::operator&(KeyCombination combination)
        {
            return *this;
        }

        KeyCombination &KeyCombination::operator|(Key key)
        {
            return *this;
        }

        KeyCombination &KeyCombination::operator|(KeyMod mod)
        {
            return *this;
        }

        KeyCombination &KeyCombination::operator|(KeyCombination combination)
        {
            return *this;
        }

        std::map<Sint32, KEY_STATE> Keyboard::key       = {};
        std::map<Sint32, Uint32>    Keyboard::timestamp = {};
        std::string                 Keyboard::text;

        void Keyboard::pollEvent(SDL_Event &event)
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(key[event.key.keysym.sym] == RELEASED)
                {
                    key[event.key.keysym.sym]       = KEY_STATE::DOWN;
                    timestamp[event.key.keysym.sym] = SYSTEM::Time::getTicks();
                }
                else if(key[event.key.keysym.sym] == KEY_STATE::DOWN)
                {
                    key[event.key.keysym.sym]       = KEY_STATE::PRESSED;
                    timestamp[event.key.keysym.sym] = SYSTEM::Time::getTicks();
                }
            }
            else if(event.type == SDL_KEYUP)
            {
                if(key[event.key.keysym.sym])
                {
                    key[event.key.keysym.sym]       = KEY_STATE::RELEASED;
                    timestamp[event.key.keysym.sym] = SYSTEM::Time::getTicks();
                }
            }
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
            return (key[sym] == KEY_STATE::PRESSED);
        }

//        bool Keyboard::pressed(Key key)
//        {
//            return false;
//        }

        bool Keyboard::down(SDL_Keycode sym)
        {
            return (key[sym] == KEY_STATE::DOWN);
        }

        bool Keyboard::released(SDL_Keycode sym)
        {
            return (key[sym] == KEY_STATE::RELEASED);
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2)
        {
            return key[sym1] && key[sym2];
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2)
        {
            return key[sym1] || key[sym2];
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3)
        {
            return key[sym1] && key[sym2] && key[sym3];
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3)
        {
            return key[sym1] || key[sym2] || key[sym3];
        }

        bool Keyboard::pressedAND(std::vector<SDL_Keycode> syms)
        {
            bool     pressed = true;
            for(auto sym : syms)
            {
                pressed = pressed && key[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed;
        }

        bool Keyboard::pressedOR(std::vector<SDL_Keycode> syms)
        {
            bool     pressed = false;
            for(auto sym : syms)
            {
                pressed = pressed || key[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed;
        }

        bool Keyboard::pressed(SDL_Keycode sym, SDL_Keymod mod)
        {
            return key[sym] && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keymod mod)
        {
            return key[sym1] && key[sym2] && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keymod mod)
        {
            return (key[sym1] || key[sym2]) && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedAND(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3, SDL_Keymod mod)
        {
            return key[sym1] && key[sym2] && key[sym3] && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedOR(SDL_Keycode sym1, SDL_Keycode sym2, SDL_Keycode sym3, SDL_Keymod mod)
        {
            return (key[sym1] || key[sym2] || key[sym3]) && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedAND(std::vector<SDL_Keycode> syms, SDL_Keymod mod)
        {
            bool     pressed = true;
            for(auto sym : syms)
            {
                pressed = pressed && key[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed && SDL_GetModState() & mod;
        }

        bool Keyboard::pressedOR(std::vector<SDL_Keycode> syms, SDL_Keymod mod)
        {
            bool     pressed = false;
            for(auto sym : syms)
            {
                pressed = pressed || key[sym];
                if(!pressed)
                {
                    return false;
                }
            }
            return pressed && SDL_GetModState() & mod;
        }
    }
}