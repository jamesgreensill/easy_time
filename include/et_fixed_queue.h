#pragma once
#include <functional>

#include "et_base.h"
#include <queue>

namespace et
{
    template <typename t_type, unsigned long long t_size>
    class fixed_queue :
        public base
    {
    public:
        // element access
        t_type front() const;
        t_type back() const;

        // capacity
        bool empty() const;
        size_t size() const;
        size_t max_size() const;

        // modifiers
        bool push(const t_type& value);
        bool emplace(const t_type& value);
        void pop();

        // lambda accessors
        void operate_pop(std::function<void(t_type)>);

    private:
        std::queue<t_type> internal_queue = {};
    };

    template <typename t_type, unsigned long long t_t_size>
    t_type fixed_queue<t_type, t_t_size>::front() const
    {
        return internal_queue.front();
    }

    template <typename t_type, unsigned long long t_size>
    t_type fixed_queue<t_type, t_size>::back() const
    {
        return internal_queue.back();
    }

    template <typename t_type, unsigned long long t_size>
    bool fixed_queue<t_type, t_size>::empty() const
    {
        return internal_queue.empty();
    }

    template <typename t_type, unsigned long long t_size>
    size_t fixed_queue<t_type, t_size>::size() const
    {
        return internal_queue.size();
    }

    template <typename t_type, unsigned long long t_size>
    size_t fixed_queue<t_type, t_size>::max_size() const
    {
        return t_size;
    }

    template <typename t_type, unsigned long long t_size>
    bool fixed_queue<t_type, t_size>::push(const t_type& value)
    {
        internal_queue.push(value);
        if (size() > t_size)
        {
            pop();
            return false;
        }
        return true;
    }

    template <typename t_type, unsigned long long t_size>
    bool fixed_queue<t_type, t_size>::emplace(const t_type& value)
    {
        internal_queue.emplace(value);
        if (size() > t_size)
        {
            std::function<void()> function;
            pop();
            return false;
        }
        return true;
    }

    template <typename t_type, unsigned long long t_size>
    void fixed_queue<t_type, t_size>::pop()
    {
        return internal_queue.pop();
    }

    template <typename t_type, unsigned long long t_t_size>
    void fixed_queue<t_type, t_t_size>::operate_pop(std::function<void(t_type)> function)
    {
        while (!empty())
        {
            function(front());
            pop();
        }
    }
}
