#ifndef TURBO_SERIES_H
#define TURBO_SERIES_H

#include <map>
#include <vector>
#include <algorithm>

namespace TURBO
{
    namespace CHART
    {
        unsigned size(std::map<float, float> data);

        float maxX(std::map<float, float> data);
        float minX(std::map<float, float> data);
        float maxY(std::map<float, float> data);
        float minY(std::map<float, float> data);

        unsigned seriesSize(std::map<unsigned, std::map<float, float>> data);

        float maxSeriesX(std::map<unsigned, std::map<float, float>> data);
        float minSeriesX(std::map<unsigned, std::map<float, float>> data);
        float maxSeriesY(std::map<unsigned, std::map<float, float>> data);
        float minSeriesY(std::map<unsigned, std::map<float, float>> data);

        class Series
        {
        private:
            std::map<unsigned, std::map<float, float>> data;

        public:
            Series();

            /*
             * Multiple series and x and y coordinates
             */
            explicit Series(std::map<unsigned, std::map<float, float>> data);

            /*
            * Multiple series and x and y coordinates
            */
            explicit Series(std::vector<std::map<float, float>> data);

            /*
             * Multiple series with y coordinates
             */
            explicit Series(std::map<unsigned, std::vector<float>> data);
            
            /*
             * Multiple series with y coordinates
             */
            explicit Series(std::vector<std::vector<float>> data);

            /*
             * One series with x and y coordinates
             */
            explicit Series(std::map<float, float> data);
            
            /*
             * One series with < coordinates
             */
            explicit Series(std::vector<float> data);

            /*
             * Multiple series and x and y coordinates
             */
            void addSeries(std::map<unsigned, std::map<float, float>> data);

            /*
            * Multiple series and x and y coordinates
            */
            void addSeries(std::vector<std::map<float, float>> data);

            /*
             * Multiple series with y coordinates
             */
            void addSeries(std::map<unsigned, std::vector<float>> data);

            /*
             * Multiple series with y coordinates
             */
            void addSeries(std::vector<std::vector<float>> data);

            /*
             * One series with x and y coordinates and index
             */
            void addSeries(unsigned index, std::map<float, float> data);

            /*
             * One series with x and y coordinates and index
             */
            void addSeries(unsigned index, std::vector<float> data);

            /*
             * One series with x and y coordinates
             */
            void addSeries(std::map<float, float> data);

            /*
             * One series with < coordinates
             */
            void addSeries(std::vector<float> data);
            
            /*
             * Returns all series
             */
            std::map<unsigned, std::map<float, float>> getSeries();

            /*
             * Returns one series at given index
             */
            std::map<float, float> getSeries(unsigned index);
        };
    }
}

#endif //TURBO_SERIES_H
