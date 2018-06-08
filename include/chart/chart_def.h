#ifndef TURBO_CHART_DEF_H
#define TURBO_CHART_DEF_H

#include "gui/main_widget.h"

namespace TURBO
{
    namespace CHART
    {
        class IChart
            : public GUI::Widget
        {
        private:
            VIDEO::Color grid_minor_color = 0xAAAAAAFF;
            VIDEO::Color grid_major_color = 0x55555555;
            Uint8        grid_minor_size  = 1;
            Uint8        grid_major_size  = 1;
            Uint8        grid_minor_dist  = 30;
            Uint8        grid_major_dist  = 100;
            bool         draw_background  = true;
            bool         draw_border      = true;
            bool         draw_grid        = true;

        public:
            explicit IChart(GUI::Object *parent);

            virtual void drawChart(VIDEO::Renderer *renderer);

            virtual void draw(VIDEO::Renderer *renderer) = 0;
        };
    }
}

#endif //TURBO_CHART_DEF_H
