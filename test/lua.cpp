#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TCH = TURBO::CHART;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

void luaScript()
{
    TS::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initTTF();
    TV::Window   win = TV::Window("Test", TM::Rect(20, 20, 400, 400), SDL_WINDOW_SHOWN);
    TV::Renderer ren = TV::Renderer(win, -1, SDL_RENDERER_ACCELERATED);
    ren.setDrawColor({255, 0, 0, 255});
    ren.setClearColor({0, 255, 0, 255});
    ren.present();
    ren.clear();

    TC::Lua l = TC::Lua();
    auto    L = l.getState();
    TC::LuaPoint::Register(L);

//    win.registerObject(L);
    l.registerObject<TV::Window>(L);

    l.callScript("resources/script/lua/test.lua");

    std::string input;
    std::getline(std::cin, input);

    while(input != "exit")
    {
        l.callString(input);
        ren.present();
        ren.clear();
        std::getline(std::cin, input);
    }
};