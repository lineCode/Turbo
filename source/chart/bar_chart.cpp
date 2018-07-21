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
            auto data = getSeries();
            float max_x = maxSeriesX(data);
            float max_y = maxSeriesY(data);

            auto factor_x = (int)std::round((space.w - plot_padding.left) / seriesSize(data));
            auto factor_y = (int)std::round((space.h - plot_padding.top) / max_y);

            auto x = (int)std::round(position.x + plot_padding.left / 2);
            auto y = (int)std::round(position.y + space.h + plot_padding.top / 2);

            VIDEO::Color colors[] = {VIDEO::RED, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN};
            auto index = 0;

            drawChart(renderer);

            renderer->drawRect({20, 20, 200, 200}, 1, VIDEO::GREEN, true);

            for(auto &e : data)
            {
                auto y_val = static_cast<int>((*(e.second.begin())).second * factor_y);
                MATH::Rect r(x, y - y_val - plot_padding.top, factor_x, y_val);
                renderer->drawRect(r, 1, colors[index], true);
                x += factor_x;
                index++;
            }
        }
    }
}