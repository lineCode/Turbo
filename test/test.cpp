#include <script/python.h>
#include <SDL_net.h>
#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

void over()
{
    std::cout << "hover" << std::endl;
}

void out()
{
    std::cout << "out" << std::endl;
}

void quit()
{
    TS::SYSTEM_RUNNING = false;
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
    auto main_widget = TG::MainWidget(window, renderer);
    auto hbox = TG::Box(&main_widget, TG::ORIENTATION::VERTICAL);
    auto vbox1 = TG::Box(nullptr, TG::ORIENTATION::HORIZONTAL);
    auto vbox2 = TG::Box(nullptr, TG::ORIENTATION::HORIZONTAL);
    auto grid = TG::Grid(nullptr, 3, 3);
    auto b1 = TG::Button("Hi");
    auto b2 = TG::Button("Bye");
    auto b3 = TG::Button("Today");
    auto b4 = TG::Button("Käse?");
    auto b5 = TG::Button("Test");
    auto b6 = TG::Button("Grid-Test");
    auto b7 = TG::Button("Grid-Test2");
    auto wi = TG::Button("Black");

    renderer.getFont()->setFontSize(60);

    b1.setBackgroundColor({255, 255, 0, 255});
    b2.setBackgroundColor({255, 0, 0, 255});
    b2.setBackgroundTexture("resources/images/mushroom.png", &renderer);
    b3.setBackgroundColor({255, 0, 255, 255});
    b4.setBackgroundColor({0, 0, 0, 255});
    b5.setBackgroundColor({0, 255, 255, 255});
    b5.setFontColor({255, 0, 50, 100});
    b5.setBorderColor({0, 255, 0, 255});
    b6.setBackgroundColor({100, 100, 100, 255});
    b6.setBackgroundColor({50, 150, 50, 255});
    b7.setBackgroundColor({100, 100, 100, 255});
    b7.setFontColor({100, 200, 255, 255});
    wi.setBackgroundColor({0, 0, 0, 0});
    wi.setFontColor({255, 0, 255, 255});

    hbox.addWidget(&vbox1);
    hbox.addWidget(&b5);
    hbox.addWidget(&vbox2);
    vbox1.addWidget(&b1);
    vbox1.addWidget(&b2);
    vbox2.addWidget(&b3);
    vbox2.addWidget(&b4);
    vbox2.addWidget(&grid);
    vbox2.addWidget(&wi);
    grid.addWidget(&b6, 0, 0, 1, 2);
    grid.addWidget(&b7, 1, 1, 2, 1);

    b7.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OVER, over);
    b7.registerCallback(TG::EVENT_TYPE::ON_MOUSE_OUT, out);
    b7.registerCallback(TG::EVENT_TYPE::ON_MOUSE_BUTTON_DOWN, quit);

    LOG("Start application");

    while(TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TI::Mouse::pollEvent(event);
            TI::Keyboard::pollEvent(event);
            main_widget.pollEvent(event);

            if(event.type == SDL_QUIT || TI::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
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

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns") << std::endl;
    return 0;
}