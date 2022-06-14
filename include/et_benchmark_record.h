#pragma once
#include "et_base.h"
#include "et_time_point_m.h"

#include "et_benchmark_result.h"
#include "et_fixed_queue.h"

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
    template<unsigned long long t_size>
    struct benchmark_record : base
    {
        et::fixed_queue<time_point_m, t_size> start_points = {};
        et::fixed_queue<time_point_m, t_size> end_points = {};
        record_state state = record_state::invalid;

        bool push_start(time_point_m point);
        bool push_end(time_point_m point);

        virtual benchmark_result to_result();
        std::string to_string() const override;

    private:
        static bool populate(et::fixed_queue<time_point_m, t_size>& collection, time_point_m point);
    };

    template <unsigned long long t_size>
    bool benchmark_record<t_size>::populate(et::fixed_queue<time_point_m, t_size>& collection, time_point_m point)
    {
        return collection.push(point);
    }

    template <unsigned long long t_size>
    bool benchmark_record<t_size>::push_start(time_point_m point)
    {
        return populate(start_points, point);
    }

    template <unsigned long long t_size>
    bool benchmark_record<t_size>::push_end(time_point_m point)
    {
        return populate(end_points, point);
    }

    template <unsigned long long t_size>
    benchmark_result benchmark_record<t_size>::to_result()
    {
        time_point_m total = { 0 };
        time_point_m highest = { -INT_MAX };
        time_point_m lowest = { INT_MAX };

        et::fixed_queue<time_point_m, t_size> sp_r = start_points;
        et::fixed_queue<time_point_m, t_size> ep_r = end_points;

        while (!sp_r.empty() && !ep_r.empty())
        {
            time_point_m start = sp_r.front();
            time_point_m end = ep_r.front();

            time_point_m difference = end - start;

            if (difference > highest)
            {
                highest = difference;
            }
            if (difference < lowest)
            {
                lowest = difference;
            }

            total = total + difference;

            sp_r.pop();
            ep_r.pop();
        }

        const time_point_m mean = total / t_size;
        benchmark_result result;

        result.highest_case = highest;
        result.lowest_case = lowest;
        result.mean_case = mean;
        result.iterations = t_size;

        return result;
    }

    template <unsigned long long t_size>
    std::string benchmark_record<t_size>::to_string() const
    {
        std::string rv;

        et::fixed_queue<time_point_m, t_size> sp_r = start_points;
        et::fixed_queue<time_point_m, t_size> ep_r = end_points;

        int iteration = 0;
        while (!sp_r.empty() && !ep_r.empty())
        {
            time_point_m start = sp_r.front();
            time_point_m end = ep_r.front();

            rv += "\titeration: " + std::to_string(iteration) + "\n";
            rv += "\t\tstart_point: " + start.flat_string() + "\n";
            rv += "\t\tend_point: " + end.flat_string() + "\n";
            rv += "\n";

            sp_r.pop();
            ep_r.pop();

            iteration++;
        }

        return rv;
    }

    /**
     * \brief Named benchmark record used for external benchmark posting.
     */
    template<unsigned long long t_size>
    struct named_benchmark_record : public benchmark_record<t_size>
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

    template <unsigned long long t_size>
    std::string named_benchmark_record<t_size>::to_string() const
    {
        std::string rv{};
        rv += "named benchmark: " + name + "\n";
        rv += static_cast<benchmark_record<t_size>>(*this).to_string();
        return rv;
    }
}
