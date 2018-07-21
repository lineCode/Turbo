#ifndef TURBO_CHART_DEF_H
#define TURBO_CHART_DEF_H

#include "gui/main_widget.h"
#include "chart/series.h"
#include "chart/chart_style.h"

namespace TURBO
{
    namespace CHART
    {
        class IChart
            : public GUI::Widget, public Series, public ChartStyle
        {
        private:
            std::string chart_title     = "";
            std::string x_axis_title    = "";
            std::string y_axis_title    = "";
            bool        draw_minor_grid = true;
            bool        draw_major_grid = true;
            bool        draw_grid       = true;

        public:
            explicit IChart(GUI::Object *parent = nullptr);

            IChart &setTitle(std::string title);

            IChart &setXAxisTitle(std::string title);

            IChart &setYAxisTitle(std::string title);

            IChart &setAxisTitle(std::string x_axis, std::string y_axis);

            IChart &setTickFormat(std::string format);

            virtual void drawChart(VIDEO::Renderer *renderer);

            virtual void draw(VIDEO::Renderer *renderer) = 0;
        };
    }
}

#endif //TURBO_CHART_DEF_H
