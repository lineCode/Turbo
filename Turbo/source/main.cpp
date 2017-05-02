#include "turbo/application.h"

using TURBO::Application;
using namespace GUI;
using namespace GEOMETRY;
using namespace AUDIO;
using namespace SCRIPT;

int main(int argc, char ** argv)
{
    Application app = Application();


    /*bool running = true;
    while(running == true)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                {
                    running = false;
                    break;
                }
            }
            game_renderer.clear();
            widget.draw(game_renderer);
            game_renderer.present();
        }
    }*/
    return app.run();
}