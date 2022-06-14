#pragma once
#include <unordered_map>

#include "et_benchmark_record.h"
#include "et_benchmark_result.h"
#include "et_time_point_m.h"

namespace et
{
#ifdef CUSTOM_MAX_BENCHMARK_RECORD_COUNT
#define MAX_BENCHMARK_RECORD_COUNT CUSTOM_MAX_BENCHMARK_RECORD_COUNT
#else
#define MAX_BENCHMARK_RECORD_COUNT 1024
#endif

    class named_benchmark
    {
    public:
        static bool post_now(const std::string& name);
        static bool post_end(const std::string& name);
        static bool start(const std::string& name);
        static benchmark_result end(const std::string& name);

    private:
        static std::unordered_map<std::string, named_benchmark_record<MAX_BENCHMARK_RECORD_COUNT>> records;
    };

    inline bool named_benchmark::post_now(const std::string& name)
    {
        const time_point_m now = time_point_m::now();

        records[name].push_start(now);

        return true;
    }

    inline bool named_benchmark::post_end(const std::string& name)
    {
        const time_point_m now = time_point_m::now();

        records[name].push_end(now);

        return true;
    }

    inline bool named_benchmark::start(const std::string& name)
    {
        const auto& it = records.find(name);
        if (it != records.end())
        {
            return false;
        }
        records.emplace(name, named_benchmark_record<MAX_BENCHMARK_RECORD_COUNT>{});
        return true;
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

    std::unordered_map<std::string, named_benchmark_record<MAX_BENCHMARK_RECORD_COUNT>> named_benchmark::records = {};
}
