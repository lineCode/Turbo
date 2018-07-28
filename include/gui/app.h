#ifndef TURBO_APP_H
#define TURBO_APP_H

#include "main_widget.h"

namespace TURBO
{
    namespace GUI
    {
        class App
        {
        private:
            SYSTEM::SDL     sdl;
            VIDEO::Window   *window;
            VIDEO::Renderer *renderer;
            MainWidget      *main_widget;

        public:
            App(std::string app_name, MATH::Rect size, Uint32 window_flags = SDL_WINDOW_SHOWN,
                Uint32 renderer_flags = SDL_RENDERER_ACCELERATED);

            ~App();

            SYSTEM::SDL &getSDL();

            VIDEO::Window &getWindow();

            VIDEO::Renderer &getRenderer();

            MainWidget &getMainWidget();

            int run();

            void attach(Widget *widget);
        };
    }
}

#endif //TURBO_APP_H
