#include "gui/app.h"

namespace TURBO
{
    namespace GUI
    {
        App::App(std::string app_name, MATH::Rect size, Uint32 window_flags, Uint32 renderer_flags)
            : window(app_name, size, window_flags),
              renderer(window, -1, renderer_flags),
              main_widget(window, renderer)
        {

        }

        VIDEO::Window &App::getWindow()
        {
            return window;
        }

        VIDEO::Renderer &App::getRenderer()
        {
            return renderer;
        }

        MainWidget &App::getMainWidget()
        {
            return main_widget;
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
                    main_widget.pollEvent(event);

                    if(event.type == SDL_QUIT || INPUT::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
                    {
                        SYSTEM::SYSTEM_RUNNING = false;
                    }

                    renderer.clear();
                    main_widget.draw(&renderer);
                    renderer.present();
                }
                SYSTEM::Clock::sleep(1);
            }
            return 0;
        }

        void App::attach(Widget &widget)
        {
            main_widget.setChild(&widget);
        }
    }
}