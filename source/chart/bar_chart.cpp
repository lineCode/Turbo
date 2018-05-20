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
        }
    }
}