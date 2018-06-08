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
                renderer->drawRect(size, 1, background_color, true);
            }
            if(draw_border)
            {
                renderer->drawRect(size, 1, border_color, false);
            }
            if(draw_grid)
            {
                for(int i = size.x; i < size.x + size.w; i += grid_minor_dist)
                {
                    renderer->drawLine(i, size.y, i, size.y + size.h, grid_minor_size, grid_minor_color);
                }
                for(int i = size.y; i < size.y + size.h; i += grid_minor_dist)
                {
                    renderer->drawLine(size.x, i, size.x + size.w, i, grid_minor_size, grid_minor_color);
                }

                for(int i = size.x; i < size.x + size.w; i += grid_major_dist)
                {
                    renderer->drawLine(i, size.y, i, size.y + size.h, grid_major_size, grid_major_color);
                }
                for(int i = size.y; i < size.y + size.h; i += grid_major_dist)
                {
                    renderer->drawLine(size.x, i, size.x + size.w, i, grid_major_size, grid_major_color);
                }
            }
        }
    }
}