#ifndef TURBO_LINE_CHART_H
#define TURBO_LINE_CHART_H

#include "chart/chart_def.h"

namespace TURBO
{
    namespace CHART
    {
        class LineChart: public IChart
        {
        private:

        public:
            explicit LineChart(GUI::Object *parent = nullptr);

            void draw(VIDEO::Renderer *renderer) override;
        };
    }
}

#endif //TURBO_LINE_CHART_H
