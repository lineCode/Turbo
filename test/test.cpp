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
    using TG::operator ""_pt;

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

    renderer.getFont()->setFontSize(14);

    b1.setBackgroundColor(TV::YELLOW);
    b2.setBackgroundColor(TV::RED);
    b2.setBackgroundTexture("resources/image/mushroom.png", &renderer);
    b3.setBackgroundColor(TV::MAGENTA);
    b4.setBackgroundColor(TV::BLACK);
    b4.setFontColor(TV::WHITE);
    b4.setTextAlignment(TV::TEXT_ALIGNMENT::MIDDLE_CENTER);
    b4.setFontSize(18_pt);
    bchart.setBackgroundColor(0xEEEEEEFF);
    bchart.setFontColor({255, 0, 50, 100});
    b6.setBackgroundColor({100, 100, 100, 255});
    b6.setBackgroundColor({50, 150, 50, 255});
    b6.setTextAlignment(TV::TEXT_ALIGNMENT::BOTTOM_RIGHT);
    b7.setBackgroundColor({100, 100, 100, 255});
    b7.setFontColor({100, 200, 255, 255});
    wi.setBackgroundColor({0, 0, 0, 0});
    wi.setFontColor({255, 0, 255, 255});
    wi.setFontStyle(TV::FONT_STYLE::BOLD_ITALIC);
    wi.setTextAlignment(TV::TEXT_ALIGNMENT::BOTTOM_CENTER);
    wi.setFontSize(14_pt);

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
            for(auto i : TM::range(TM::Point(275,280), TM::Point(325,280), TM::Point(25,0)))
            {
                for(auto j : TM::range(TM::Point(250,350), TM::Point(350,350), TM::Point(10,0)))
                {
                    renderer.drawLine(i, j, 10, TURBO::VIDEO::RED);
                }
            }
            for(auto i : TM::range(TM::Line(400,280,375,350), TM::Line(475,280,525,350), TM::Line(25, 0, 50, 0)))
            {
                renderer.drawLine(i, 10, TURBO::VIDEO::RED);
            }
            renderer.present();
        }
        SDL_Delay(5);
    }

    LOG("Stop application");
}

PyMODINIT_FUNC PyInit_Turbo(void)
{
    Py_Initialize();
    PyObject *m = PyModule_Create(&TURBO::SCRIPT::Turbo_definition);

    if(PyType_Ready(&TURBO::SCRIPT::RectType) < 0)
        return nullptr;

    Py_INCREF(&TURBO::SCRIPT::RectType);
    PyModule_AddObject(m, "Rect", (PyObject * ) & TURBO::SCRIPT::RectType);

    return m;
}

void python(int argc, char ** argv)
{
    wchar_t *program = Py_DecodeLocale(argv[0], nullptr);
    if (program == nullptr) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("Turbo", PyInit_Turbo);

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    PyRun_SimpleString("import Turbo \nb = Turbo.Rect(4, 3, 4, 5)\nprint(b.x)");

    PyMem_RawFree(program);
}

int main(int argc, char **argv)
{
    TS::PTimer ptimer{};

    //gui();
    python(argc, argv);

    std::cout << "Execution took: "
              << TS::Clock::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns")
              << std::endl;
    return 0;
}
