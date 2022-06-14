#pragma once
#include <string>

namespace et
{
    /**
     * \brief base class for all things easy_time.
     * Provides a common interface for all easy_time related classes.
     */
    struct base
    {
        virtual ~base() = default;
        virtual std::string to_string() const;
    };
    inline std::string base::to_string() const
    {
        return __FUNCTION__;
    }
}
