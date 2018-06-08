#include <gui/units.h>
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

void gui()
{
    LOG("Loading libraries");

    TS::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initMIX(MIX_INIT_MP3 | MIX_INIT_FLAC);
    sdl.initTTF();

    LOG("Set up UI");

    auto window      = TV::Window("Title", TM::Rect(50, 50, 600, 600), SDL_WINDOW_SHOWN);
    auto renderer    = TV::Renderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto main_widget = TG::MainWidget(window, renderer);
    auto hbox        = TG::Box(&main_widget, TG::ORIENTATION::VERTICAL);
    auto vbox1       = TG::Box(nullptr, TG::ORIENTATION::HORIZONTAL);
    auto vbox2       = TG::Box(nullptr, TG::ORIENTATION::HORIZONTAL);
    auto grid        = TG::Grid(nullptr, 3, 3);
    auto b1          = TG::Button("Hi");
    auto b2          = TG::Button("Bye");
    auto b3          = TG::Button("Today");
    auto b4          = TG::Button("Käse?");
    auto bchart      = TCH::BarChart(nullptr);
    auto b6          = TG::Button("Grid-Test");
    auto b7          = TG::Button("Grid-Test2");
    auto wi          = TG::Button("Black");

    LOG("Configure");

    renderer.getFont()->setFontSize(60);

    b1.setBackgroundColor(TV::YELLOW);
    b2.setBackgroundColor(TV::RED);
    b2.setBackgroundTexture("resources/image/mushroom.png", &renderer);
    b3.setBackgroundColor(TV::MAGENTA);
    b4.setBackgroundColor(TV::BLACK);
    b4.setFontColor(TV::WHITE);
    bchart.setBackgroundColor(0xEEEEEEFF);
    bchart.setFontColor({255, 0, 50, 100});
    b6.setBackgroundColor({100, 100, 100, 255});
    b6.setBackgroundColor({50, 150, 50, 255});
    b7.setBackgroundColor({100, 100, 100, 255});
    b7.setFontColor({100, 200, 255, 255});
    wi.setBackgroundColor({0, 0, 0, 0});
    wi.setFontColor({255, 0, 255, 255});

    LOG("Insert Widgets");

    hbox.addWidget(&vbox1);
    hbox.addWidget(&bchart);
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

    using TURBO::GUI::operator""_pt;

    auto px = 15_pt;
    std::cout << px << std::endl;

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
            renderer.drawRect(20, 20, 200, 200, 1, TV::TRANSPARENT, true);
            renderer.present();
        }
        SDL_Delay(5);
    }

    LOG("Stop application");
}

void cmdParser(int argc, char **argv)
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

    for(const auto &arg : cmd_parser.getArgument("-w"))
    {
        std::cout << arg << " ";
    }
    std::cout << "\n";
}

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
//    win.registerObject(L);
    l.registerObject<TV::Window>(L);

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

void musicPlayer()
{
    TS::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initMIX(MIX_INIT_FLAC | MIX_INIT_MP3);

    TV::Window      window       = TV::Window();
    TA::MediaPlayer media_player = TA::MediaPlayer(TURBO::TURBO_AUDIO_PATH);
    media_player.play();
    media_player.setVolume(0);

    while(media_player.isPlaying() && TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TI::Keyboard::pollEvent(event);

            if(event.type == SDL_QUIT || TI::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
            {
                TS::SYSTEM_RUNNING = false;
            }

            if(TI::Keyboard::pressedOR(SDLK_PLUS, SDLK_KP_PLUS, SDLK_UP))
            {
                media_player.setVolume(media_player.getVolume() + 5);
            }
            else if(TI::Keyboard::pressedOR(SDLK_MINUS, SDLK_KP_MINUS, SDLK_DOWN))
            {
                media_player.setVolume(media_player.getVolume() - 5);
            }

            if(TI::Keyboard::pressed(SDLK_RIGHT, KMOD_LCTRL))
            {
                media_player.next();
            }
            else if(TI::Keyboard::pressed(SDLK_LEFT, KMOD_LCTRL))
            {
                media_player.previous();
            }
            else if(TI::Keyboard::pressedOR(SDLK_RIGHT, SDLK_l))
            {
                media_player.setPosition(media_player.getPosition() + 100);
            }
            else if(TI::Keyboard::pressedOR(SDLK_LEFT, SDLK_k))
            {
                media_player.setPosition(media_player.getPosition() - 100);
            }

            if(TI::Keyboard::down(SDLK_SPACE))
            {
                if(media_player.isPaused())
                {
                    LOG("PLAY");
                    media_player.resume();
                }
                else
                {
                    LOG("PAUSE");
                    media_player.pause();
                }
            }
        }
        SDL_Delay(5);
    }
}

int server()
{
    TS::SDL sdl = TS::SDL();
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initNET();


    LOG("START SERVER");

    TN::TCPServer server = TN::TCPServer(13370);
    TN::NetPackage package{};

    Uint16 text[] = {0x050a, 0x0065, 0x006c, 0x006c,
                     0x006f, 0x0020, 0x02ac, 0x006f,
                     0x0072, 0x006c, 0x0064, 0x0020,
                     0x0074, 0x006f, 0x0020, 0x03a8,
                     0x006f, 0x0075, 0x0020, 0x006d,
                     0x0079, 0x0020, 0x0066, 0x0072,
                     0x0069, 0x20ac, 0x006e, 0x0064,
                     0x002e, 0x0020, 0xfc00, 0x0020,
                     0x0904, 0x0020, 0x10F7, 0x1435};

    std::copy(text, text + sizeof(text)/ sizeof(Uint16), package.data);

    // Wait for 1 Client, wait at max 10 sec
    server.waitAccept(1, 10000);

    server.send(package);

    while(!server.receive(package))
    {
        SDL_Delay(200);
    }

    package.print();

    return 0;
}

int client()
{
    TS::SDL sdl = TS::SDL();
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initNET();


    TN::TCPClient  client = TN::TCPClient("127.0.0.1", 13370);
    TN::NetPackage package{};

    while(!client.receive(package))
    {
        SDL_Delay(200);
    }

    package.print();

    package.data[TN::PACKAGE_BUFFER] = {0};
    Uint16 text[] = {0x050A, 0x0065, 0x006C, 0x006C,
                     0x006F, 0x0020, 0x15F7, 0x0020,
                     0x15C6, 0x0020, 0x18B7, 0x0020,
                     0x1729};


    std::copy(text, text + sizeof(text)/ sizeof(Uint16), package.data);

    client.send(package);


    return 0;
}

int keyboard()
{
    TS::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    TV::Window      window       = TV::Window();
    TI::KeyCombination comb1 = TI::KeyCombination(SDLK_a);
    TI::KeyCombination comb2 = TI::KeyCombination(TI::Key{SDLK_q});

    comb1 &= SDLK_s;
    comb1 &= TI::Key{SDLK_d} & TI::Key{SDLK_f};

    comb2 |= TI::Key{SDLK_w};
    comb2 &= TI::Key{SDLK_e} & TI::Key{SDLK_r};


    while(TS::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            TI::Keyboard::pollEvent(event);

            if(event.type == SDL_QUIT || TI::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
            {
                TS::SYSTEM_RUNNING = false;
            }

            if(TI::Keyboard::down(comb1))
            {
                LOG("Key combination 1");
            }
            if(TI::Keyboard::down(comb2))
            {
                LOG("Key combination 2");
            }
        }
    }
    return 0;
}

int database()
{
    TU::DB_SQLITE sqlite{"resources/db.sqlite"};

    TU::DB_MYSQL mysql{"localhost", "root", "root"};
    mysql.dropDatabase("Turbo");
    mysql.createDatabase("Turbo");
    mysql.useDatabase("Turbo");

    mysql.createTable("Cars",
                       std::vector<std::string>{"Id", "Name", "Price"},
                       std::vector<std::string>{"INT", "TEXT", "INT"},
                       std::vector<std::string>{},
                       std::vector<std::string>{},
                       std::vector<std::string>{},
                       std::vector<std::string>{},
                       std::vector<std::string>{"PRIMARY KEY"});

    mysql.insertEntry("Cars", std::vector<std::string>{"Id", "Name", "Price"},
                      std::vector<std::string>{"0", "Test", "100"});

    for(auto & query : mysql.getQueryCache())
    {
        LOG(query);
    }
    return 0;
}


int main(int argc, char **argv)
{
    TS::PTimer ptimer{};

    gui();

    std::cout << TS::Clock::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns") << std::endl;
    return 0;
}