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
            return code < other.getCode();
        }

        KeyCombination Key::operator&(Key other)
        {
            KeyCombination key_comb = KeyCombination(Key{other.getCode()});
            return key_comb &= Key(code);
        }

        KeyCombination Key::operator|(Key other)
        {
            KeyCombination key_comb = KeyCombination(Key{other.getCode()});
            return key_comb |= Key(code);
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

        Sint64 Key::getCode() const
        {
            return code;
        }

        KeyMod::KeyMod(SDL_Keymod mod)
            : code(mod)
        {

        }

        KeyMod::KeyMod(KEYMOD mod)
            : code(mod)
        {

        }

        KeyMod::KeyMod(Key &code)
            : code(code.getCode())
        {

        }

        Sint64 KeyMod::getMod()
        {
            return code;
        }

        Key KeyMod::getKey()
        {
            return Key(code);
        }

        KeyCombination::KeyCombination(SDL_Keycode keycode)
        {
            combs.insert(std::set<Key>{Key{keycode}});
        }

        KeyCombination::KeyCombination(SDL_Keymod keymod)
        {
            combs.insert(std::set<Key>{KeyMod{keymod}.getKey()});
        }

        KeyCombination::KeyCombination(Key key)
        {
            combs.insert(std::set<Key>{key});
        }

        KeyCombination::KeyCombination(KeyMod mod)
        {
            combs.insert(std::set<Key>{mod.getKey()});
        }

        std::set<std::set<Key>> KeyCombination::getComb()
        {
            return combs;
        }

        KeyCombination &KeyCombination::operator&(SDL_Keycode keycode)
        {
            *this &= keycode;
            return *this;
        }

        KeyCombination &KeyCombination::operator&=(SDL_Keycode keycode)
        {
            for(auto & comb : combs)
            {
                auto c = comb;
                c.insert(Key{keycode});
                combs.erase(comb);
                combs.insert(c);
            }
            return *this;
        }

        KeyCombination &KeyCombination::operator&(SDL_Keymod keymod)
        {
            *this &= keymod;
            return *this;
        }

        KeyCombination &KeyCombination::operator&=(SDL_Keymod keymod)
        {
            for(auto & comb : combs)
            {
                auto c = comb;
                c.insert(Key{keymod});
                combs.erase(comb);
                combs.insert(c);
            }
            return *this;
        }

        KeyCombination &KeyCombination::operator&(Key key)
        {
            *this &= key;
            return *this;
        }

        KeyCombination &KeyCombination::operator&=(Key key)
        {
            for(auto & comb : combs)
            {
                auto c = comb;
                c.insert(key);
                combs.erase(comb);
                combs.insert(c);
            }
            return *this;
        }

        KeyCombination &KeyCombination::operator&(KeyMod mod)
        {
            *this &= mod;
            return *this;
        }

        KeyCombination &KeyCombination::operator&=(KeyMod mod)
        {
            for(auto & comb : combs)
            {
                auto c = comb;
                c.insert(mod.getKey());
                combs.erase(comb);
                combs.insert(c);
            }
            return *this;
        }

        KeyCombination &KeyCombination::operator&(KeyCombination combination)
        {
            *this &= combination;
            return *this;
        }

        KeyCombination &KeyCombination::operator&=(KeyCombination combination)
        {
            for(auto & first : combs)
            {
                for(auto & second : combination.getComb())
                {
                    auto c = first;
                    for(auto k : second)
                    {
                        c.insert(k);
                    }
                    combs.erase(first);
                    combs.insert(c);
                }
            }
            return *this;
        }

        KeyCombination &KeyCombination::operator|(SDL_Keycode keycode)
        {
            *this |= keycode;
            return *this;
        }

        KeyCombination &KeyCombination::operator|=(SDL_Keycode keycode)
        {
            combs.insert(std::set<Key>{Key{keycode}});
            return *this;
        }

        KeyCombination &KeyCombination::operator|(SDL_Keymod keymod)
        {
            *this |= keymod;
            return *this;
        }

        KeyCombination &KeyCombination::operator|=(SDL_Keymod keymod)
        {
            combs.insert(std::set<Key>{Key{keymod}});
            return *this;
        }

        KeyCombination &KeyCombination::operator|(Key key)
        {
            *this |= key;
            return *this;
        }

        KeyCombination &KeyCombination::operator|=(Key key)
        {
            combs.insert(std::set<Key>{key});
            return *this;
        }

        KeyCombination &KeyCombination::operator|(KeyMod mod)
        {
            *this |= mod;
            return *this;
        }

        KeyCombination &KeyCombination::operator|=(KeyMod mod)
        {
            combs.insert(std::set<Key>{mod.getKey()});
            return *this;
        }

        KeyCombination &KeyCombination::operator|(KeyCombination combination)
        {
            *this |= combination;
            return *this;
        }

        KeyCombination &KeyCombination::operator|=(KeyCombination combination)
        {
            for(auto & second : combination.getComb())
            {
                combs.insert(second);
            }
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
                    timestamp[event.key.keysym.sym] = SYSTEM::Clock::getTicks();
                }
                else if(key[event.key.keysym.sym] == KEY_STATE::DOWN)
                {
                    key[event.key.keysym.sym]       = KEY_STATE::PRESSED;
                    timestamp[event.key.keysym.sym] = SYSTEM::Clock::getTicks();
                }
            }
            else if(event.type == SDL_KEYUP)
            {
                if(key[event.key.keysym.sym])
                {
                    key[event.key.keysym.sym]       = KEY_STATE::RELEASED;
                    timestamp[event.key.keysym.sym] = SYSTEM::Clock::getTicks();
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


        bool Keyboard::pressed(KeyCombination comb)
        {
            for(auto & c : comb.getComb())
            {
                bool pressed = true;
                for(auto & k : c)
                {
                    pressed = pressed && (key[k.getCode()] == KEY_STATE::PRESSED);
                }
                if(pressed)
                {
                    return true;
                }
            }
            return false;
        }

        bool Keyboard::pressed(SDL_Keycode sym)
        {
            return (key[sym] == KEY_STATE::PRESSED);
        }

        bool Keyboard::pressed(Key k)
        {
            return (key[k.getCode()] == KEY_STATE::PRESSED);
        }

        bool Keyboard::down(KeyCombination comb)
        {
            for(auto & c : comb.getComb())
            {
                bool pressed = true;
                for(auto & k : c)
                {
                    pressed = pressed && (key[k.getCode()] >= KEY_STATE::DOWN);
                }
                if(pressed)
                {
                    return true;
                }
            }
            return false;
        }

        bool Keyboard::down(SDL_Keycode sym)
        {
            return (key[sym] >= KEY_STATE::DOWN);
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
            for(auto & sym : syms)
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
            for(auto & sym : syms)
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
            for(auto & sym : syms)
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
            for(auto & sym : syms)
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