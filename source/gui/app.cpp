#include "gui/app.h"

namespace TURBO
{
    namespace GUI
    {
        App::App(std::string app_name, MATH::Rect size, Uint32 window_flags, Uint32 renderer_flags)
        {
            sdl.initSDL(SDL_INIT_EVERYTHING);
            sdl.initIMG(IMG_INIT_PNG);
            sdl.initTTF();

            window = new VIDEO::Window(app_name, size, window_flags);
            renderer = new VIDEO::Renderer(*window, -1, renderer_flags);
            main_widget = new MainWidget(*window, *renderer);
        }

        App::~App()
        {
            delete window;
            delete renderer;
            delete main_widget;
        }

        SYSTEM::SDL &App::getSDL()
        {
            return sdl;
        }

        VIDEO::Window &App::getWindow()
        {
            return *window;
        }

        VIDEO::Renderer &App::getRenderer()
        {
            return *renderer;
        }

        MainWidget &App::getMainWidget()
        {
            return *main_widget;
        }

        int App::run()
        {
            while(SYSTEM::SYSTEM_RUNNING)
            {
                SDL_Event event = {};
                while(SDL_PollEvent(&event))
                {
                    INPUT::Mouse::pollEvent(event);
                    INPUT::Keyboard::pollEvent(event);
                    main_widget->pollEvent(event);

                    if(event.type == SDL_QUIT || INPUT::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
                    {
                        SYSTEM::SYSTEM_RUNNING = false;
                    }
                    if(event.type == SDL_MOUSEMOTION)
                    {

                    }

                    renderer->clear();
                    main_widget->draw(renderer);
                    renderer->present();
                }
                SYSTEM::Clock::sleep(1);
            }
            return 0;
        }

        void App::attach(Widget *widget)
        {
            main_widget->setChild(widget);
        }
    }
}