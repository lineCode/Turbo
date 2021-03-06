#include <iostream>
#include "chart/series.h"

namespace TURBO
{
    namespace CHART
    {
        unsigned size(std::map<float, float> data)
        {
            return static_cast<unsigned>(data.size());
        }

        float maxX(std::map<float, float> data)
        {
            auto el = std::max_element(data.begin(), data.end(),
                                       [](const std::pair<float, float> &el1, const std::pair<float, float> &el2)
                                       {
                                           return el1.first < el2.first;
                                       });
            return el->first;
        }

        float minX(std::map<float, float> data)
        {
            auto el = std::max_element(data.begin(), data.end(),
                                       [](const std::pair<float, float> &el1, const std::pair<float, float> &el2)
                                       {
                                           return el1.first > el2.first;
                                       });
            return el->first;
        }

        float maxY(std::map<float, float> data)
        {
            auto el = std::max_element(data.begin(), data.end(),
                                       [](const std::pair<float, float> &el1, const std::pair<float, float> &el2)
                                       {
                                           return el1.second < el2.second;
                                       });
            return el->second;
        }

        float minY(std::map<float, float> data)
        {
            auto el = std::max_element(data.begin(), data.end(),
                                       [](const std::pair<float, float> &el1, const std::pair<float, float> &el2)
                                       {
                                           return el1.second > el2.second;
                                       });
            return el->second;
        }

        unsigned seriesSize(std::map<unsigned, std::map<float, float>> data)
        {
            unsigned data_size = 0;
            for(auto & series : data)
            {
                unsigned group_size = size(series.second);
                data_size = data_size > group_size ? data_size : group_size;
            }
            return data_size;
        }

        float maxSeriesX(std::map<unsigned, std::map<float, float>> data)
        {
            float val = (*(data.begin())->second.begin()).first;

            for(auto & series : data)
            {
                float el = maxX(series.second);
                val = val > el ? val : el;
            }
            return val;
        }

        float minSeriesX(std::map<unsigned, std::map<float, float>> data)
        {
            float val = (*(data.begin())->second.begin()).first;

            for(auto & series : data)
            {
                float el = minX(series.second);
                val = val < el ? val : el;
            }
            return val;
        }

        float maxSeriesY(std::map<unsigned, std::map<float, float>> data)
        {
            float val = (*(data.begin())->second.begin()).second;

            for(auto & series : data)
            {
                float el = maxY(series.second);
                val = val > el ? val : el;
            }
            return val;
        }

        float minSeriesY(std::map<unsigned, std::map<float, float>> data)
        {
            float val = (*(data.begin())->second.begin()).second;

            for(auto & series : data)
            {
                float el = minY(series.second);
                val = val < el ? val : el;
            }
            return val;
        }

        Series::Series()
        {

        }

        Series::Series(std::map<unsigned, std::map<float, float>> data)
            : data(std::move(data))
        {

        }

        Series::Series(std::vector<std::map<float, float>> data)
        {
            for(auto &series : data)
            {
                addSeries(this->series_count++, series);
            }
        }

        Series::Series(std::map<unsigned, std::vector<float>> data)
        {
            for(auto &series : data)
            {
                addSeries(series.first, series.second);
            }
        }

        Series::Series(std::vector<std::vector<float>> data)
        {
            for(auto &series : data)
            {
                addSeries(this->series_count++, series);
            }
        }

        Series::Series(std::map<float, float> data)
        {
            addSeries(this->series_count++, data);
        }

        Series::Series(std::vector<float> data)
        {
            addSeries(this->series_count++, data);
        }

        Series &Series::addSeries(std::map<unsigned, std::map<float, float>> data)
        {
            for(auto &series : data)
            {
                addSeries(series.first, series.second);
            }
            return *this;
        }

        Series &Series::addSeries(std::vector<std::map<float, float>> data)
        {
            for(auto &series : data)
            {
                addSeries(this->series_count++, series);
            }
            return *this;
        }

        Series &Series::addSeries(std::map<unsigned, std::vector<float>> data)
        {
            for(auto &series : data)
            {
                addSeries(series.first, series.second);
            }
            return *this;
        }

        Series &Series::addSeries(std::vector<std::vector<float>> data)
        {
            for(auto &series : data)
            {
                addSeries(series_count++, series);
            }
            return *this;
        }

        Series &Series::addSeries(unsigned index, std::map<float, float> data)
        {
            this->data[index] = data;
            return *this;
        }

        Series &Series::addSeries(unsigned index, std::vector<float> data)
        {
            unsigned entry_index = 0;

            for(auto &entry : data)
            {
                this->data[index][entry_index++] = entry;
            }
            return *this;
        }

        Series &Series::addSeries(std::map<float, float> data)
        {
            this->data[series_count++] = data;
            return *this;
        }

        Series &Series::addSeries(std::vector<float> data)
        {
            float index = 0;
            for(auto &entry : data)
            {
                this->data[series_count][index++] = entry;
            }
            series_count++;
            return *this;
        }

        std::map<unsigned, std::map<float, float>> Series::getSeries()
        {
            return this->data;
        }

        std::map<float, float> Series::getSeries(unsigned index)
        {
            return this->data[index];
        }

        unsigned Series::getSeriesCount()
        {
            return series_count;
        }
    }
}