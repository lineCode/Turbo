#include "turbo.h"

namespace TV = TURBO::VIDEO;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TS = TURBO::SYSTEM;

int main(int argc, char ** argv)
{
    TS::PTimer ptimer{};

    TS::SDL sdl(SDL_INIT_EVERYTHING);
    TS::SDLTTF ttf;
    auto window = TV::Window("Title", TM::Rect(50, 50, 500, 500), SDL_WINDOW_SHOWN);
    auto renderer = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = new TURBO::GUI::MainWidget(window, renderer);
    auto vbox = new TURBO::GUI::Box(main_widget);
    auto b1 = new TURBO::GUI::Button("Hi");
    auto b2 = new TURBO::GUI::Button("Bye");

    vbox->addWidget(b1);
    vbox->addWidget(b2);

    renderer.clear();
    renderer.drawObject(main_widget);
    renderer.present();

    SDL_Delay(500);

    renderer.clear();
    renderer.drawObject(main_widget);
    renderer.present();

    SDL_Delay(500);

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%Ss %fms %uus %nns") << std::endl;

    delete b1;
    delete b2;
    delete vbox;
    delete main_widget;
    return 0;
}