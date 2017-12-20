    #include "turbo.h"

namespace TURBO
{
    Uint32 Settings::SDL_INIT_FLAGS = SDL_INIT_EVERYTHING;
    Uint32 Settings::IMG_INIT_FLAGS = IMG_INIT_PNG;
    Uint32 Settings::MIX_INIT_FLAGS = MIX_INIT_MP3;

    Uint8 Settings::TURBO_FRAME_LIMIT = 60;

    Turbo::Turbo()
        : sdl(Settings::SDL_INIT_FLAGS),
          frame_limit(Settings::TURBO_FRAME_LIMIT)
    {
        sdl.initIMG(Settings::IMG_INIT_FLAGS);
        sdl.initMIX(Settings::MIX_INIT_FLAGS);
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
                ren.clear();
                ren.present();
            }
        }
        return 0;
    }
}