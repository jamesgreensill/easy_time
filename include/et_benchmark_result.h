#pragma once
#include "et_base.h"
#include "et_time_point_m.h"

namespace et
{
    struct benchmark_result :
        public base
    {
    public:
        long long iterations{};
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
}
