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

void musicPlayer()
{
    TS::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initMIX(MIX_INIT_FLAC | MIX_INIT_MP3);

    TV::Window      window       = TV::Window("test", {0, 0, 200, 200}, 0);
    TA::MediaPlayer media_player = TA::MediaPlayer(TURBO::TURBO_AUDIO_PATH);
    media_player.play();
    media_player.setVolume(0);

    while(media_player.isPlaying() && TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TI::Keyboard::pollEvent(&event);

            if(event.type == SDL_QUIT || TI::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
            {
                TS::SYSTEM_RUNNING = false;
            }

            if(TI::Keyboard::pressedOR(SDLK_PLUS, SDLK_KP_PLUS, SDLK_UP))
            {
                media_player.setVolume(media_player.getVolume() + 5);
            }
            else if(TI::Keyboard::pressedOR(SDLK_MINUS, SDLK_KP_MINUS, SDLK_DOWN))
            {
                media_player.setVolume(media_player.getVolume() - 5);
            }

            if(TI::Keyboard::pressed(SDLK_RIGHT, KMOD_LCTRL))
            {
                media_player.next();
            }
            else if(TI::Keyboard::pressed(SDLK_LEFT, KMOD_LCTRL))
            {
                media_player.previous();
            }
            else if(TI::Keyboard::pressedOR(SDLK_RIGHT, SDLK_l))
            {
                media_player.setPosition(media_player.getPosition() + 100);
            }
            else if(TI::Keyboard::pressedOR(SDLK_LEFT, SDLK_k))
            {
                media_player.setPosition(media_player.getPosition() - 100);
            }

            if(TI::Keyboard::down(SDLK_SPACE))
            {
                if(media_player.isPaused())
                {
                    LOG("PLAY");
                    media_player.resume();
                }
                else
                {
                    LOG("PAUSE");
                    media_player.pause();
                }
            }
        }
        SDL_Delay(5);
    }
}