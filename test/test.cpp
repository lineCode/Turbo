#include "turbo.h"

using namespace TURBO;

int main(int argc, char **argv)
{
    SYSTEM::PTimer ptimer{};

    using namespace TURBO;
    using GUI::operator ""_pt;
    using GUI::operator ""_px;

    TURBO::SYSTEM::SDL sdl{};
    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initIMG(IMG_INIT_PNG);
    sdl.initTTF();

//    auto app = GUI::App("My App", MATH::Rect(20, 20, 1024, 768), 0, 0);
//
//    app.getMainWidget().setBackgroundColor(VIDEO::TRANSPARENT);
//    app.getRenderer().setClearColor(VIDEO::BLACK);
//
//    auto grid          = GUI::Grid(nullptr, 12, 12);
//    auto char_icon     = GUI::Button("");
//    auto char_stat_box = GUI::Box(nullptr, GUI::ORIENTATION::VERTICAL);
//    auto life_bar      = GUI::Button("Life");
//    auto stamina_bar   = GUI::Button("Stamina");
//
//    grid.setBackgroundColor(VIDEO::TRANSPARENT);
//    char_icon.setBackgroundColor(VIDEO::TRANSPARENT);
//    char_icon.setBackgroundTexture("resources/image/icon.png", &app.getRenderer());
//    char_icon.setOpacity(0.5);
//    life_bar.setTextAlignment(VIDEO::TEXT_ALIGNMENT::MIDDLE_CENTER);
//    life_bar.setBackgroundColor(VIDEO::RED);
//    stamina_bar.setTextAlignment(VIDEO::TEXT_ALIGNMENT::MIDDLE_CENTER);
//    stamina_bar.setBackgroundColor(VIDEO::LIME);
//
//    app.getMainWidget().setChild(&grid);
//
//    grid.addWidget(&char_icon, 0, 0, 1, 2);
//    grid.addWidget(&char_stat_box, 1, 0, 2, 1);
//
//    char_stat_box.addWidget(&life_bar);
//    char_stat_box.addWidget(&stamina_bar);
//
//    app.run();


    auto window = VIDEO::Window("auto", {200, 200, 600, 600}, 0);
    auto renderer = VIDEO::Renderer(window, -1, 0);
    auto main_widget = GUI::MainWidget(window, renderer);
    auto scroll_widget = GUI::ScrollArea();
    auto label = GUI::TextWidget(&scroll_widget, "adsd");

    label.setFontSize(200);
    label.setBackgroundColor(VIDEO::RED);

    main_widget.setChild(&scroll_widget);

    while(SYSTEM::SYSTEM_RUNNING)
    {
        SDL_Event event = {};
        while(SDL_PollEvent(&event))
        {
            INPUT::Mouse::pollEvent(&event);
            INPUT::Keyboard::pollEvent(&event);
            main_widget.pollEvent(&event);

            if(event.type == SDL_QUIT || INPUT::Keyboard::pressed(SDLK_ESCAPE, KMOD_LCTRL))
            {
                SYSTEM::SYSTEM_RUNNING = false;
            }

            renderer.clear();
            main_widget.draw(&renderer);
            renderer.present();
        }
        SYSTEM::Clock::sleep(1);
    }

    std::cout << "Execution took: "
              << SYSTEM::Clock::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns")
              << "\n";

    return 0;
}
