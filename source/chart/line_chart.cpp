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

            auto padding_x = (int)std::round(space.w / 3); // 1/3 padding 2/3 diagram
            auto padding_y = (int)std::round(space.h / 3);

            auto factor_x = (int)std::round((space.w - padding_x) / seriesSize(data));
            auto factor_y = (int)std::round((space.h -padding_y) / max_y);

            VIDEO::Color colors[] = {VIDEO::RED, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN};
            auto index = 0;

            drawChart(renderer);

            renderer->drawRect({20, 20, 200, 200}, 1, VIDEO::GREEN, true);

            for(auto &series : data)
            {
                auto x = static_cast<int>((*series.second.begin()).first + padding_x / 2);
                auto y = static_cast<int>((*series.second.begin()).second - padding_y / 2);
                for(auto &entry : series.second)
                {
                    auto x_val = (int)std::round(entry.first * factor_x);
                    auto y_val = (int)std::round(entry.second * factor_y);

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