#include "chart/chart_def.h"

namespace TURBO
{
    namespace CHART
    {
        IChart::IChart(GUI::Object *parent)
            : GUI::Widget(parent)
        {
            setMinorGrid(VIDEO::GREY5, 30, 40, 1, 1);
            setMajorGrid(VIDEO::GREYA, 40, 50, 1, 1);
        }

        IChart &IChart::setTitle(std::string title)
        {
            chart_title = std::move(title);
            return *this;
        }

        IChart &IChart::setXAxisTitle(std::string title)
        {
            x_axis_title = std::move(title);
            return *this;
        }

        IChart &IChart::setYAxisTitle(std::string title)
        {
            y_axis_title = std::move(title);
            return *this;
        }

        IChart &IChart::setAxisTitle(std::string x_axis, std::string y_axis)
        {
            setXAxisTitle(std::move(x_axis));
            setYAxisTitle(std::move(y_axis));
            return *this;
        }

        IChart &IChart::setTickFormat(std::string format)
        {
            return *this;
        }

        void IChart::drawChart(VIDEO::Renderer *renderer)
        {
            /* Minor Grid */
            if(draw_grid || draw_minor_grid)
            {
                for(int i = size.x; i < size.x + size.w; i += minor_grid.x_dist)
                {
                    renderer->drawLine(MATH::Line(i, size.y, i, size.y + size.h), minor_grid.x_size, minor_grid.color);
                }
                for(int i = size.y; i < size.y + size.h; i += minor_grid.y_dist)
                {
                    renderer->drawLine(MATH::Line(size.x, i, size.x + size.w, i), minor_grid.y_size, minor_grid.color);
                }

            }

            /* Major Grid */
            if(draw_grid || draw_major_grid)
            {
                for(int i = size.x; i < size.x + size.w; i += major_grid.x_dist)
                {
                    renderer->drawLine(MATH::Line(i, size.y, i, size.y + size.h), major_grid.x_size, major_grid.color);
                }
                for(int i = size.y; i < size.y + size.h; i += major_grid.y_dist)
                {
                    renderer->drawLine(MATH::Line(size.x, i, size.x + size.w, i), major_grid.y_size, major_grid.color);
                }
            }
        }
    }
}