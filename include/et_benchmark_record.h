#pragma once
#include <vector>

#include "et_base.h"
#include "et_time_point_m.h"

#include "et_benchmark_result.h"

namespace et
{
    enum struct record_state : bool
    {
        invalid,
        valid
    };

    /**
     * \brief Benchmark record used for the internal benchmark system.
     */
    template<unsigned long long size>
    struct benchmark_record : base
    {
        time_point_m* start_points = new time_point_m[size];
        time_point_m* end_points = new time_point_m[size];
        record_state state = record_state::invalid;

        bool push_start() const;
        bool push_end() const;

        virtual benchmark_result to_result();
        std::string to_string() const override;
        ~benchmark_record() override;

    private:
        static bool populate(time_point_m* collection, time_point_m point);
    };

    template <unsigned long long size>
    benchmark_record<size>::~benchmark_record()
    {
        delete[] start_points;
        delete[] end_points;
    }

    template <unsigned long long size>
    bool benchmark_record<size>::populate(time_point_m* collection, time_point_m point)
    {
        time_point_m* ptr = collection;
        if (ptr == nullptr)
        {
            return false;
        }

        for (int i = 0; i < size; i++)
        {
            ptr = &collection[i];
            if (!ptr)
            {
                collection[i] = point;
                return true;
            }
        }
        return false;
    }

    template <unsigned long long size>
    bool benchmark_record<size>::push_start() const
    {
        return populate(start_points, time_point_m::now());
    }

    template <unsigned long long size>
    bool benchmark_record<size>::push_end() const
    {
        return populate(end_points, time_point_m::now());
    }

    template <unsigned long long size>
    benchmark_result benchmark_record<size>::to_result()
    {
        time_point_m total = { 0 };
        time_point_m highest = { -INT_MAX };
        time_point_m lowest = { INT_MAX };
        for (unsigned long long i = 0; i < size; i++)
        {
            time_point_m time_difference = end_points[i] - start_points[i];
            if (time_difference >= highest)
            {
                highest = time_difference;
            }
            if (time_difference < lowest)
            {
                lowest = time_difference;
            }

            total = total + time_difference;
        }

        const time_point_m mean = total / size;
        benchmark_result result;

        result.highest_case = highest;
        result.lowest_case = lowest;
        result.mean_case = mean;
        result.iterations = size;

        return result;
    }

    template <unsigned long long size>
    std::string benchmark_record<size>::to_string() const
    {
        std::string rv;
        for (int i = 0; i < size; i++)
        {
            rv += "\titeration: " + std::to_string(i) + "\n";
            rv += "\t\tstart_point: " + this->start_points[i].flat_string() + "\n";
            rv += "\t\tend_point: " + this->end_points[i].flat_string() + "\n";
            rv += "\n";
        }
        return rv;
    }

    /**
     * \brief Named benchmark record used for external benchmark posting.
     */
    template<unsigned long long size>
    struct named_benchmark_record : public benchmark_record<size>
    {
        // name of the record.
        std::string name;

        /**
         * \brief Converts this data to a string.
         * \return
         * NAME: name<br>
         * ITERATION: (number)<br>
         * POINT_DATA: point.to_string()<br>
         */
        std::string to_string() const override;
    };

    template <unsigned long long size>
    std::string named_benchmark_record<size>::to_string() const
    {
        std::string rv{};
        rv += "named benchmark: " + name + "\n";
        rv += static_cast<benchmark_record<size>>(*this).to_string();
        return rv;
    }
}
