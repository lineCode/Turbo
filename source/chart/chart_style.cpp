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
    }
}