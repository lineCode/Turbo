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

            auto padding_x = (int)std::round(space.w / 3); // 1/3 padding 2/3 diagram
            auto padding_y = (int)std::round(space.h / 3);

            auto factor_x = (int)std::round((space.w - padding_x) / seriesSize(data));
            auto factor_y = (int)std::round((space.h -padding_y) / max_y);

            auto x = (int)std::round(position.x + padding_x / 2);
            auto y = (int)std::round(position.y + space.h + padding_y / 2);

            VIDEO::Color colors[] = {VIDEO::RED, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN,
                                     VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN, VIDEO::BLUE, VIDEO::GREEN};
            auto index = 0;

            drawChart(renderer);

            renderer->drawRect({20, 20, 200, 200}, 1, VIDEO::GREEN, true);

            for(auto &e : data)
            {
                auto y_val = static_cast<int>((*(e.second.begin())).second * factor_y);
                MATH::Rect r(x, y - y_val - padding_y, factor_x, y_val);
                renderer->drawRect(r, 1, colors[index], true);
                x += factor_x;
                index++;
            }
        }
    }
}