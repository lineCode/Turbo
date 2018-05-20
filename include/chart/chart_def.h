#ifndef TURBO_CHART_DEF_H
#define TURBO_CHART_DEF_H

#include "gui/main_widget.h"

namespace TURBO
{
    namespace CHART
    {
        class IChart : public GUI::Widget
        {
        private:
            bool draw_background = true;
            bool draw_border = true;
            std::set<std::pair<MATH::Point, MATH::Point>> grid;
            VIDEO::Color grid_color = {0, 0, 0, 128};
            Uint8 grid_minor = 1;
            Uint8 grid_major = 1;
            bool draw_grid = true;

        public:
            explicit IChart(GUI::Object *parent);

            template <typename T>
            bool setData(T data)
            {
                return false;
            }

            virtual void drawChart(VIDEO::Renderer *renderer);

            virtual void draw(VIDEO::Renderer *renderer) = 0;
        };
    }
}

#endif //TURBO_CHART_DEF_H
