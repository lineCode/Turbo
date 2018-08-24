#ifndef TURBO_CHART_STYLE_H
#define TURBO_CHART_STYLE_H

#include "gui/units.h"
#include "math/space.h"
#include "video/texture.h"
#include "video/color.h"

namespace TURBO
{
    namespace CHART
    {
        struct Grid
        {
            VIDEO::Color color  = VIDEO::BLACK;
            Uint8        x_size = 1;
            Uint8        x_dist = 30;
            Uint8        y_size = 1;
            Uint8        y_dist = 50;

            Grid();

            Grid(VIDEO::COLOR color, Uint8 x_dist, Uint8 y_dist, Uint8 x_size, Uint8 y_size);
        };

        class ChartStyle
        {
        protected:
            MATH::Space     chart_padding;
            MATH::Space     plot_padding;
            Grid           minor_grid;
            Grid           major_grid;
            VIDEO::Texture *plot_background_texture = nullptr;
            VIDEO::Color   plot_background_color    = VIDEO::WHITE;

        public:
            ChartStyle();

            ChartStyle &setChartPadding(Uint32 t, Uint32 r, Uint32 b, Uint32 l);

            ChartStyle &setChartPadding(Uint32 padding);

            ChartStyle &setPlotPadding(Uint32 t, Uint32 r, Uint32 b, Uint32 l);

            ChartStyle &setPlotPadding(Uint32 padding);

            ChartStyle &setMinorGrid(VIDEO::COLOR color, Uint8 x_dist, Uint8 y_dist, Uint8 x_size, Uint8 y_size);

            ChartStyle &setMajorGrid(VIDEO::COLOR color, Uint8 x_dist, Uint8 y_dist, Uint8 x_size, Uint8 y_size);
        };
    }
}

#endif //TURBO_CHART_STYLE_H
