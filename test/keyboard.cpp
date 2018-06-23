#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TCH = TURBO::CHART;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

void keyboard()
{
    TS::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    TV::Window         window = TV::Window();
    TI::KeyCombination comb1  = TI::KeyCombination(SDLK_a);
    TI::KeyCombination comb2  = TI::KeyCombination(TI::Key{SDLK_q});

    comb1 &= SDLK_s;
    comb1 &= TI::Key{SDLK_d} & TI::Key{SDLK_f};

    comb2 |= TI::Key{SDLK_w};
    comb2 &= TI::Key{SDLK_e} & TI::Key{SDLK_r};


    while(TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TI::Keyboard::pollEvent(event);

            if(event.type == SDL_QUIT || TI::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
            {
                TS::SYSTEM_RUNNING = false;
            }

            if(TI::Keyboard::down(comb1))
            {
                LOG("Key combination 1");
            }
            if(TI::Keyboard::down(comb2))
            {
                LOG("Key combination 2");
            }
        }
    }
}