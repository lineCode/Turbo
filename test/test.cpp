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

    LOG("Loading libraries");

    TS::SDL sdl = TS::SDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initMIX(MIX_INIT_MP3 | MIX_INIT_FLAC);
    sdl.initTTF();

    LOG("Set up UI");

    auto window = TV::Window("Title", TM::Rect(50, 50, 600, 600), SDL_WINDOW_SHOWN);
    auto renderer = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = TURBO::GUI::MainWidget(window, renderer);
    auto hbox = TURBO::GUI::Box(&main_widget, TURBO::GUI::ORIENTATION::VERTICAL);
    auto vbox1 = TURBO::GUI::Box(nullptr, TURBO::GUI::ORIENTATION::HORIZONTAL);
    auto vbox2 = TURBO::GUI::Box(nullptr, TURBO::GUI::ORIENTATION::HORIZONTAL);
    auto b1 = TURBO::GUI::Button("Hi");
    auto b2 = TURBO::GUI::Button("Bye");
    auto b3 = TURBO::GUI::Button("Today");
    auto b4 = TURBO::GUI::Button("Asd\nss\nsda");
    auto b5 = TURBO::GUI::Button("Test");

    b1.setBackground(TURBO::GUI::Background({255, 255, 0, 255}));
    b2.setBackground(TURBO::GUI::Background({255, 0, 0, 255}));
    b3.setBackground(TURBO::GUI::Background({255, 0, 255, 255}));
    b4.setBackground(TURBO::GUI::Background({0, 0, 0, 255}));
    b5.setBackground(TURBO::GUI::Background({0, 255, 255, 255}));
    hbox.addWidget(&vbox1);
    hbox.addWidget(&b5);
    hbox.addWidget(&vbox2);
    vbox1.addWidget(&b1);
    vbox1.addWidget(&b2);
    vbox2.addWidget(&b3);
    vbox2.addWidget(&b4);

    b1.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OVER, color);
    b1.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OUT, out);

    LOG("Start application");

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

    LOG("Stop application");

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%s %fms %uus %nns") << std::endl;
    return 0;
}