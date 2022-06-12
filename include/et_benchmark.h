#pragma once
#include <iostream>
#include <thread>
#include <vector>

#include "et_base.h"
#include "et_time_point_m.h"

namespace et
{
    struct benchmark_result : base
    {
        long long iterations;
        time_point_m highest_case;
        time_point_m lowest_case;
        time_point_m mean_case;

        inline std::string to_string() const override;
    };

    inline std::string benchmark_result::to_string() const
    {
        std::string rv = {};
        rv += "\n----------------------------\n";
        rv += "Iterations: ";
        rv += std::to_string(iterations);
        rv += "\n";
        rv += "Highest Case.\n";
        rv += highest_case.flat_string();
        rv += "\n";
        rv += "Lowest Case\n";
        rv += lowest_case.flat_string();
        rv += "\n";
        rv += "Average.\n";
        rv += mean_case.flat_string();
        rv += "\n----------------------------\n";
        return rv;
    }

    class benchmark : public base
    {
        virtual void iterate() = 0;
    public:
        template <typename t, size_t iterations>
        static benchmark_result run();
    };

    template <typename t, size_t iterations>
    benchmark_result benchmark::run()
    {
        static_assert(std::is_base_of<benchmark, t>(), "t must be a subclass of benchmark");
        benchmark* _benchmark = new t();

        time_point_m* differences = new time_point_m[iterations];
        std::cout << "Allocating: " << sizeof(time_point_m) * iterations << " bytes." << std::endl;

        for (int i = 0; i < iterations; i++)
        {
            const auto start = time_point_m();
            _benchmark->iterate();
            const auto end = time_point_m();
            const auto difference = end - start;

            differences[i] = difference;
        }

        time_point_m total = { 0 };
        time_point_m highest = { -INT_MAX };
        time_point_m lowest = { INT_MAX };
        for (int i = 0; i < iterations; i++)
        {
            time_point_m time_difference = differences[i];
            if (time_difference >= highest)
            {
                highest = time_difference;
                std::cout << "HIGHEST CHANGED TO: " << highest.flat_string() << " iteration: " << i << std::endl;
            }
            if (time_difference < lowest)
            {
                lowest = time_difference;
                std::cout << "LOWEST CHANGED TO: " << lowest.flat_string() << " iteration: " << i << std::endl;
            }

            total = total + time_difference;
        }

        const time_point_m mean = total / iterations;
        benchmark_result result = benchmark_result{};

        result.highest_case = highest;
        result.lowest_case = lowest;
        result.mean_case = mean;
        result.iterations = iterations;

        delete[] differences;
        delete _benchmark;

        return result;
    }
}
