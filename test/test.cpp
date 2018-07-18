#include "turbo.h"

using namespace TURBO;

int main(int argc, char **argv)
{
    SYSTEM::PTimer ptimer{};

    SYSTEM::SDL sdl{};

    sdl.initSDL(SDL_INIT_EVERYTHING);
    sdl.initTTF();

    GUI::App app = GUI::App("MyApp", {50, 50, 500, 500});
    auto b_chart = CHART::LineChart();
    b_chart.addSeries({{1,2,4,8,16}, {2,8,16,32,64}});
    app.attach(b_chart);

    app.run();


    std::cout << "Execution took: "
              << SYSTEM::Clock::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns")
              << "\n";
    return 0;
}
