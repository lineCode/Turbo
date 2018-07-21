#include "chart/line_chart.h"

namespace TURBO
{
    namespace CHART
    {
        LineChart::LineChart(GUI::Object *parent)
            : IChart(parent)
        {

        }

        void LineChart::draw(VIDEO::Renderer *renderer)
        {
            auto data = getSeries();
            float max_x = maxSeriesX(data);
            float max_y = maxSeriesY(data);

            auto factor_x = (int)std::round((space.w - plot_padding.left) / max_x);
            auto factor_y = (int)std::round((space.h - plot_padding.top) / max_y);

            VIDEO::Color colors[] = {VIDEO::RED, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN};
            auto index = 0;

            drawChart(renderer);

            for(auto &series : data)
            {
                auto x = (int)std::round((*series.second.begin()).first * factor_x) + plot_padding.left / 2;
                auto y = (int)std::round((*series.second.begin()).second * factor_y) + plot_padding.top / 2;
                for(auto &entry : series.second)
                {
                    auto x_val = (int)std::round(entry.first * factor_x) + plot_padding.left / 2;
                    auto y_val = (int)std::round(entry.second * factor_y) + plot_padding.top / 2;

                    MATH::Line l(x, space.h - y, x_val, space.h - y_val);
                    renderer->drawLine(l, 1, colors[index]);

                    x = x_val;
                    y = y_val;
                }
                index++;
            }
        }
    }
}