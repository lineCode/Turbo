#include "chart/chart_def.h"

namespace TURBO
{
    namespace CHART
    {
        IChart::IChart(GUI::Object *parent)
            : GUI::Widget(parent)
        {

        }

        void IChart::drawChart(VIDEO::Renderer *renderer)
        {
            if(draw_background)
            {
                renderer->drawRect(geometry, 1, background_color, true);
            }
            if(draw_border)
            {
                renderer->drawRect(geometry, 1, border_color, false);
            }
            if(draw_grid)
            {
                renderer->drawLine(geometry.bottomRight(), geometry.center(), 1, {0, 0, 0, 128});
                renderer->drawLine(geometry.bottomLeft(), geometry.center(), 1, {0, 0, 0, 128});
//                for(auto & p : grid)
//                {
//                    renderer->drawLine(p.first, p.second, grid_major, grid_color);
//                }
            }
        }
    }
}