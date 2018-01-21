#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TV = TURBO::VIDEO;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TS = TURBO::SYSTEM;

void color()
{
    std::cout << "hover" << std::endl;
}

void out()
{
    std::cout << "out" << std::endl;
}

void d(int x)
{
    std::cout << x << std::endl;
}

int main(int argc, char ** argv)
{
    TS::PTimer ptimer{};

    TS::SDL sdl = TS::SDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initMIX(MIX_INIT_MP3 | MIX_INIT_FLAC);
    sdl.initTTF();

    auto window = TV::Window("Title", TM::Rect(50, 50, 600, 600), SDL_WINDOW_SHOWN);
    auto renderer = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = TURBO::GUI::MainWidget(window, renderer);
    auto vbox = TURBO::GUI::Box(&main_widget, TURBO::GUI::ORIENTATION::VERTICAL);
    auto b1 = TURBO::GUI::Button("Hi");
    auto b2 = TURBO::GUI::Button("Bye");
    auto b3 = TURBO::GUI::Button("Today");

    b1.setBackground(TURBO::GUI::Background({255, 255, 0, 255}));
    b2.setBackground(TURBO::GUI::Background({255, 0, 0, 255}));
    b3.setBackground(TURBO::GUI::Background({255, 0, 255, 255}));
    vbox.addWidget(&b1);
    vbox.addWidget(&b2);
    vbox.addWidget(&b3);

    b1.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OVER, color);
    b1.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OUT, out);

    while(TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TURBO::INPUT::Mouse::pollEvent(event);
            b1.pollEvent(event);
            if(event.type == SDL_KEYDOWN)
            {
                TS::SYSTEM_RUNNING = false;
            }
            renderer.clear();
            main_widget.draw(&renderer);
            renderer.present();
        }
        SDL_Delay(5);
    }

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%Ss %fms %uus %nns") << std::endl;

    return 0;
}