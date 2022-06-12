#pragma once
#include <chrono>
#include <ostream>

#include "et_base.h"

namespace et
{
#define tp_cast(value, type) std::chrono::time_point_cast<std::chrono::type>(value).time_since_epoch().count()

    using hrc = std::chrono::high_resolution_clock;
    using tp_hrc = std::chrono::time_point<hrc>;

    using nanoseconds = std::chrono::nanoseconds;
    using microseconds = std::chrono::microseconds;
    using milliseconds = std::chrono::milliseconds;
    using seconds = std::chrono::seconds;
    using minutes = std::chrono::minutes;
    using hours = std::chrono::hours;

    struct time_point final : public base
    {
        time_point();
        time_point(const long long& milliseconds);
        time_point(const tp_hrc& point);

        tp_hrc now;

        long long nanoseconds;
        long long microseconds;
        long long milliseconds;
        long long seconds;
        long long minutes;
        long long hours;

        time_point operator+(const time_point& other) const;
        time_point operator-(const time_point& other) const;
        time_point operator*(const long long& other) const;
        // ostream operator overload
        friend std::ostream& operator<<(std::ostream& os, const et::time_point& point);
    };

    inline std::ostream& operator<<(std::ostream& os, const et::time_point& point)
    {
        os << "nano-seconds: " << point.nanoseconds << '\n';
        os << "micro-seconds: " << point.microseconds << '\n';
        os << "milli-seconds: " << point.milliseconds << '\n';
        os << "seconds: " << point.seconds << '\n';
        os << "minutes: " << point.minutes << '\n';
        os << "hours: " << point.hours << '\n';

        return os;
    }

    inline time_point::time_point() : time_point(hrc::now()) {}

    inline time_point::time_point(const long long& milliseconds) : time_point(tp_hrc(et::milliseconds(milliseconds))) {}

    inline time_point::time_point(const tp_hrc& point)
    {
        now = point;
        nanoseconds = tp_cast(point, nanoseconds);
        microseconds = tp_cast(point, microseconds);
        milliseconds = tp_cast(point, milliseconds);
        seconds = tp_cast(point, seconds);
        minutes = tp_cast(point, minutes);
        hours = tp_cast(point, hours);
    }

    inline time_point time_point::operator+(const time_point& other) const
    {
        time_point rv = {};
        rv.nanoseconds = nanoseconds + other.nanoseconds;
        rv.microseconds = microseconds + other.microseconds;
        rv.milliseconds = milliseconds + other.milliseconds;
        rv.seconds = seconds + other.seconds;
        rv.minutes = minutes + other.minutes;
        rv.hours = hours + other.hours;
        return rv;
    }

    inline time_point time_point::operator-(const time_point& other) const
    {
        time_point rv = {};
        rv.nanoseconds = nanoseconds - other.nanoseconds;
        rv.microseconds = microseconds - other.microseconds;
        rv.milliseconds = milliseconds - other.milliseconds;
        rv.seconds = seconds - other.seconds;
        rv.minutes = minutes - other.minutes;
        rv.hours = hours - other.hours;
        return rv;
    }

    inline time_point time_point::operator*(const long long& other) const
    {
        time_point rv = {};
        rv.nanoseconds = nanoseconds * other;
        rv.microseconds = microseconds * other;
        rv.milliseconds = milliseconds * other;
        rv.seconds = seconds * other;
        rv.minutes = minutes * other;
        rv.hours = hours * other;
        return rv;
    }
}
