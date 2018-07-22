#include "turbo.h"

using namespace TURBO;

int main(int argc, char **argv)
{
    SYSTEM::PTimer ptimer{};

    using namespace TURBO;
    using GUI::operator""_pt;

    auto app = GUI::App("My App", MATH::Rect(20, 20, 1024, 768));
    auto w = GUI::Widget(nullptr);
    auto grid = GUI::Grid(nullptr, 3, 3);
    auto b = GUI::Button("asdasd");
    auto s = GUI::Button("asdaaa");

    app.attach(&w);

    w.setChild(&grid);

    grid.addWidget(&b, 0, 0, 1, 1);
    grid.addWidget(&s, 0, 1, 2, 1);

    b.setBackgroundColor(VIDEO::RED);
    b.setFontSize(51_pt);
    b.setTextAlignment(VIDEO::TEXT_ALIGNMENT::MIDDLE_CENTER);

    s.setBackgroundColor(VIDEO::GREY5);
    s.setFontSize(53_pt);
    s.setTextAlignment(VIDEO::TEXT_ALIGNMENT::BOTTOM_RIGHT);

    app.run();

    std::cout << "Execution took: "
              << SYSTEM::Clock::getPTicksToString(ptimer.getTime(), "%Mm %Ss %fms %uus %nns")
              << "\n";
    return 0;
}
