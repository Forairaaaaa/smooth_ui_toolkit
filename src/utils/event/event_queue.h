/**
 * @file event_queue.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <functional>
#include <queue>
#include <mutex>

namespace smooth_ui_toolkit {

/**
 * @brief Just a queue with a mutex
 *
 * @tparam T
 */
template <typename T>
class EventQueue {
public:
    std::mutex mutex;
    std::queue<T> events;

    void emit(const T& event)
    {
        std::lock_guard<std::mutex> lock(mutex);
        events.push(event);
    }

    void poll(std::function<void(const T&)> onEvent)
    {
        std::lock_guard<std::mutex> lock(mutex);
        while (!events.empty()) {
            onEvent(events.front());
            events.pop();
        }
    };

    T front()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return events.front();
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(mutex);
        events.pop();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return events.empty();
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(mutex);
        return events.size();
    }
};

} // namespace smooth_ui_toolkit
