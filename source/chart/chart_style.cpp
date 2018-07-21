#include "chart/chart_style.h"

namespace TURBO
{
    namespace CHART
    {
        Grid::Grid()
        {

        }

        Grid::Grid(VIDEO::COLOR color, Uint8 x_dist, Uint8 y_dist, Uint8 x_size, Uint8 y_size)
            : color(color), x_dist(x_dist), y_dist(y_dist), x_size(x_size), y_size(y_size)
        {

        }

        ChartStyle::ChartStyle()
            : chart_padding(),
              plot_padding(),
              minor_grid(),
              major_grid()
        {

        }

        ChartStyle &ChartStyle::setChartPadding(Uint32 t, Uint32 r, Uint32 b, Uint32 l)
        {
            chart_padding.setSpace(t, r, b, l);
            return *this;
        }

        ChartStyle &ChartStyle::setChartPadding(Uint32 padding)
        {
            chart_padding.setSpace(padding, padding, padding, padding);
            return *this;
        }

        ChartStyle &ChartStyle::setPlotPadding(Uint32 t, Uint32 r, Uint32 b, Uint32 l)
        {
            plot_padding.setSpace(t, r, b, l);
            return *this;
        }

        ChartStyle &ChartStyle::setPlotPadding(Uint32 padding)
        {
            plot_padding.setSpace(padding, padding, padding, padding);
            return *this;
        }

        ChartStyle &ChartStyle::setMinorGrid(VIDEO::COLOR color, Uint8 x_dist, Uint8 y_dist, Uint8 x_size, Uint8 y_size)
        {
            minor_grid.color = color;
            minor_grid.x_dist = x_dist;
            minor_grid.y_dist = y_dist;
            minor_grid.x_size = x_size;
            minor_grid.y_size = y_size;

            return *this;
        }

        ChartStyle &ChartStyle::setMajorGrid(VIDEO::COLOR color, Uint8 x_dist, Uint8 y_dist, Uint8 x_size, Uint8 y_size)
        {
            major_grid.color = color;
            major_grid.x_dist = x_dist;
            major_grid.y_dist = y_dist;
            major_grid.x_size = x_size;
            major_grid.y_size = y_size;

            return *this;
        }
    }
}