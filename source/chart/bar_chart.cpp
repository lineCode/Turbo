#include "chart/bar_chart.h"

namespace TURBO
{
    namespace CHART
    {
        BarChart::BarChart(GUI::Object *parent)
            : IChart(parent)
        {

        }

        void BarChart::draw(VIDEO::Renderer *renderer)
        {
            drawChart(renderer);
            std::vector<std::pair<double, double>> d;

            d.emplace_back(1, 5);
            d.emplace_back(2, 7);
            d.emplace_back(3, 9);

            auto max_val = 9;

            auto padding_x = (int)std::round(space.w / 3);
            auto padding_y = (int)std::round(space.h / 5);
            auto factor_x = (int)std::round((space.w - padding_x) / d.size());
            auto factor_y = (int)std::round((space.h -padding_y) / max_val);

            auto x = (int)std::round(position.x + padding_x / 2);
            auto y = (int)std::round(position.y + space.h + padding_y / 2);

            VIDEO::Color colors[] = {VIDEO::RED, VIDEO::GREEN, VIDEO::BLUE};
            auto index = 0;

            for(auto e : d)
            {
                auto y_val = static_cast<int>(e.second * factor_y);
                MATH::Rect r(x, y - y_val - padding_y, factor_x, y_val);
                renderer->drawRect(r, 1, colors[index], true);
                x += factor_x;
                index++;
            }
        }
    }
}