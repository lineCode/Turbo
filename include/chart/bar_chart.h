#ifndef TURBO_BAR_CHART_H
#define TURBO_BAR_CHART_H

#include "chart/chart_def.h"

namespace TURBO
{
    namespace CHART
    {
        class BarChart: public IChart
        {
        private:

        public:
            explicit BarChart(GUI::Object *parent);

            void draw(VIDEO::Renderer *renderer) override;
        };
    }
}

#endif //TURBO_BAR_CHART_H
