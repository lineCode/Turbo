#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TV = TURBO::VIDEO;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TS = TURBO::SYSTEM;

void callback()
{
    std::cout << "ASD" << std::endl;
}

int main(int argc, char ** argv)
{
    TS::PTimer ptimer{};

    TS::SDL sdl = TS::SDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initMIX(MIX_INIT_MP3 | MIX_INIT_FLAC);

    auto window = TV::Window("Title", TM::Rect(50, 50, 500, 500), SDL_WINDOW_SHOWN);
    auto renderer = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = TURBO::GUI::MainWidget(window, renderer);
    auto vbox = TURBO::GUI::Box(&main_widget, TURBO::GUI::ORIENTATION::HORIZONTAL);
    auto b1 = TURBO::GUI::Button("Hi");
    auto b2 = TURBO::GUI::Button("Bye");
    auto b3 = TURBO::GUI::Button("Today");

    b1.setBackground(TURBO::GUI::Background({255, 255, 0, 255}));
    b2.setBackground(TURBO::GUI::Background({255, 0, 0, 255}));
    b3.setBackground(TURBO::GUI::Background({255, 0, 255, 255}));
    vbox.addWidget(&b1);
    vbox.addWidget(&b2);
    vbox.addWidget(&b3);

    auto t = TS::SDLTimer(2000, &callback);

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYDOWN)
            {
                running = false;
            }
            renderer.clear();
            renderer.drawLayout(&vbox);
            renderer.present();
        }
        SDL_Delay(5);
    }

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%Ss %fms %uus %nns") << std::endl;

    return 0;
}