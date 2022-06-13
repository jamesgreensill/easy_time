#pragma once
#include <iostream>
#include <unordered_map>

#include "et_base.h"
#include "et_time_point_m.h"
#include "et_benchmark_result.h"
#include "et_benchmark_record.h"

namespace et
{
    constexpr int k_max_benchmark_record_count = 1024;

    class named_benchmark
    {
        static void post_now(const std::string& name);
        static void post_end(const std::string& name);
        static benchmark_result end(const std::string& name);

        static std::unordered_map<std::string, named_benchmark_record<k_max_benchmark_record_count>> records;
    };

    inline void named_benchmark::post_now(const std::string& name)
    {
        const auto& it = records.find(name);
        if (it != records.end())
        {
            if (!it->second.push_start())
            {
                std::cout << "failed to post start for benchmark " << name << std::endl;
            }
        }
        else records.emplace(name, named_benchmark_record<k_max_benchmark_record_count>{});
    }

    inline void named_benchmark::post_end(const std::string& name)
    {
        const auto& it = records.find(name);
        if (it != records.end())
        {
            if (!it->second.push_end())
            {
                std::cout << "failed to post end for benchmark " << name << std::endl;
            }
        }
    }

    inline benchmark_result named_benchmark::end(const std::string& name)
    {
        const auto& it = records.find(name);
        if (it != records.end())
        {
            auto rv = it->second;
            records.erase(it);
            rv.state = record_state::valid;
            return rv.to_result();
        }
        return {};
    }

    std::unordered_map<std::string, named_benchmark_record<k_max_benchmark_record_count>> named_benchmark::records = {};
}
