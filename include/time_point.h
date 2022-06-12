#pragma once
#include <chrono>

namespace et
{
#define tp_cast(value, type) std::chrono::time_point_cast<std::chrono::type>(value).time_since_epoch().count()

    typedef std::chrono::high_resolution_clock hrc;
    typedef std::chrono::time_point<hrc> tp_hrc;

    typedef std::chrono::nanoseconds nanoseconds;
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::minutes minutes;
    typedef std::chrono::hours hours;

    struct time_point
    {
        time_point();
        time_point(long long milliseconds);
        time_point(tp_hrc point);

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

    inline time_point::time_point(long long milliseconds) : time_point(tp_hrc(et::milliseconds(milliseconds))) {}

    inline time_point::time_point(tp_hrc point)
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
        time_point rv = *this;
        rv.nanoseconds += other.nanoseconds;
        rv.microseconds += other.microseconds;
        rv.milliseconds += other.milliseconds;
        rv.seconds += other.seconds;
        rv.minutes += other.minutes;
        rv.hours += other.hours;
        return rv;
    }

    inline time_point time_point::operator-(const time_point& other) const
    {
        time_point rv = *this;
        rv.nanoseconds -= other.nanoseconds;
        rv.microseconds -= other.microseconds;
        rv.milliseconds -= other.milliseconds;
        rv.seconds -= other.seconds;
        rv.minutes -= other.minutes;
        rv.hours -= other.hours;
        return rv;
    }

    inline time_point time_point::operator*(const long long& other) const
    {
        time_point rv = *this;
        rv.nanoseconds *= other;
        rv.microseconds *= other;
        rv.milliseconds *= other;
        rv.seconds *= other;
        rv.minutes *= other;
        rv.hours *= other;
        return rv;
    }
}
