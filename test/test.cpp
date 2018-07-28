#include "turbo.h"

using namespace TURBO;

int main(int argc, char **argv)
{
    SYSTEM::PTimer ptimer{};

    using namespace TURBO;
    using GUI::operator ""_pt;

    auto app = GUI::App("My App", MATH::Rect(20, 20, 1024, 768), SDL_WINDOW_SKIP_TASKBAR | SDL_WINDOW_BORDERLESS, SDL_RENDERER_ACCELERATED);

    SDL_SetWindowOpacity(app.getWindow().getWindow(), 0.2);

    auto grid          = GUI::Grid(nullptr, 12, 12);
    auto char_icon     = GUI::Button("");
    auto char_stat_box = GUI::Box(nullptr, GUI::ORIENTATION::VERTICAL);
    auto life_bar      = GUI::Button("Life");
    auto stamina_bar   = GUI::Button("Stamina");

    grid.setBackgroundColor(VIDEO::TRANSPARENT);
    char_icon.setBackgroundTexture("resources/image/icon.png", &app.getRenderer());
    life_bar.setTextAlignment(VIDEO::TEXT_ALIGNMENT::MIDDLE_CENTER);
    life_bar.setBackgroundColor(VIDEO::RED);
    stamina_bar.setTextAlignment(VIDEO::TEXT_ALIGNMENT::MIDDLE_CENTER);
    stamina_bar.setBackgroundColor(VIDEO::LIME);

    app.getMainWidget().setChild(&grid);

    grid.addWidget(&char_icon, 0, 0, 1, 1);
    grid.addWidget(&char_stat_box, 1, 0, 2, 1);

    char_stat_box.addWidget(&life_bar);
    char_stat_box.addWidget(&stamina_bar);

    app.run();

    std::cout << "Execution took: "
              << SYSTEM::Clock::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns")
              << "\n";
    return 0;
}
