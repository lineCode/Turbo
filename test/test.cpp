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

void test()
{
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

}

void test2(int argc, char ** argv)
{
    TS::CMDParser cmd_parser = TS::CMDParser(argc, argv);

    cmd_parser.setOption("-w", "--wasp", 2, false, {}, "bzzz");
    cmd_parser.setOption("-o", "--ouch", 99, false, {}, "muh");
    cmd_parser.setOption("-l", "--loop", 1, false, {}, "sets level of looping");
    cmd_parser.setOption("-p", "--pressure", 1, true, {}, "dummy");

    if(!cmd_parser.checkArgs())
    {
        std::cout << TU::Log::format(TU::LOG_FORMAT::FG_YELLOW, "Trace:\n" + cmd_parser.getTrace())
                  << std::endl;
    }
    if(cmd_parser.isSet("-h"))
        cmd_parser.printHelp();

    for(const auto & arg : cmd_parser.getArgument("-w"))
    {
        std::cout << arg << " ";
    }
    std::cout << "\n";
}

int add(lua_State * state)
{
    int args = lua_gettop(state);
    if(args == 2)
    {
        lua_pushnumber(state, lua_tonumber(state, 1) + lua_tonumber(state, 2));
        return 1;
    }
    return -1;
}

int sub(lua_State * state)
{
    int args = lua_gettop(state);
    if(args == 2)
    {
        lua_pushnumber(state, lua_tonumber(state, 1) - lua_tonumber(state, 2));
        return 1;
    }
    return -1;
}

void test3()
{
    TC::Lua lua = TC::Lua();
    lua.registerFunction("add", add);
    lua.registerFunction("sub", sub);
    lua.callString("function div(a, b) return a/b end");
    lua.getGlobal("div");
    if(!lua_isfunction(lua.getState(),-1))
    {
        lua_pop(lua.getState(),1);
        return;
    }

    std::string call;
    double result = 0;
    std::cin >> call;

    while((result = lua.callString(call)) != -1 && !call.empty())
    {
        std::cout << result << std::endl;
        std::cin >> call;
    }
}



int main(int argc, char ** argv)
{
    TS::PTimer ptimer{};

    test4();

    std::cout << TS::Time::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns") << std::endl;
    return 0;
}