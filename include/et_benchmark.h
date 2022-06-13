#pragma once
#include <iostream>
#include <thread>
#include <vector>

#include "et_base.h"
#include "et_time_point_m.h"
#include "et_benchmark_result.h"
#include "et_benchmark_record.h"

namespace et
{
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

        benchmark_record<iterations> _record;

        for (int i = 0; i < iterations; i++)
        {
            _record.start_points[i] = time_point_m::now();
            _benchmark->iterate();
            _record.end_points[i] = time_point_m::now();
        }

        delete _benchmark;

        return _record.to_result();
    }
}
