#include "turbo.h"

namespace TURBO
{
    Uint32 Settings::SDL_INIT_FLAGS = 0x2;
    Uint32 Settings::IMG_INIT_FLAGS = IMG_INIT_PNG;
    Uint32 Settings::MIX_INIT_FLAGS = MIX_INIT_MP3;

    Turbo::Turbo(Uint32 sdl_flags)
        : sdl(sdl_flags),
          sdl_image(Settings::IMG_INIT_FLAGS),
          sdl_mixer(Settings::MIX_INIT_FLAGS),
          sdl_ttf(),
          sdl_net()
    {

    }

    void Turbo::setFrameLimit(Uint8 limit)
    {
        frame_limit = limit;
    }

    Uint8 Turbo::getFrameLimit()
    {
        return frame_limit;
    }

    int Turbo::run()
    {
        SDL_Event event;
        bool running = true;
        VIDEO::Window win("Test", MATH::Rect(0, 0, 500, 500), SDL_WINDOW_SHOWN);
        VIDEO::Renderer ren(win, -1, SDL_RENDERER_ACCELERATED);
        GUI::MainWidget widget = GUI::MainWidget(win, ren);

        while(running)
        {
            while(SDL_PollEvent(&event))
            {
                INPUT::Keyboard::pollEvent(event);
                INPUT::Mouse::pollEvent(event);
                widget.pollEvent(event);

                if(INPUT::Keyboard::pressed(SDLK_ESCAPE, KMOD_LSHIFT)
                   || INPUT::Mouse::pressed(SDL_BUTTON_RIGHT)
                   || event.type == SDL_QUIT)
                {
                    running = false;
                }
            }
        }
        return 0;
    }

    Turbo::~Turbo()
    {

    }
}