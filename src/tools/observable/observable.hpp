/**
 * @file observable.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2026-06-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

namespace smooth_ui_toolkit {

/**
 * @brief Observable value with multiple observers, no mutex.
 *
 * @tparam T
 */
template <typename T>
class Observable {
public:
    using OnChangedCallback = void (*)(void* context, const T& newValue);

    explicit Observable(T defaultValue) : _value(std::move(defaultValue)) {}

    Observable(const Observable&) = delete;
    Observable& operator=(const Observable&) = delete;
    Observable(Observable&&) = delete;
    Observable& operator=(Observable&&) = delete;

    void set(const T& newValue)
    {
        _value = newValue;
        notify();
    }

    void set(T&& newValue)
    {
        _value = std::move(newValue);
        notify();
    }

    const T& get() const
    {
        return _value;
    }

    size_t observe(void* context, OnChangedCallback callback)
    {
        size_t id = ++_last_id;
        _observers.push_back({id, context, callback});
        if (callback) {
            callback(context, _value);
        }
        return id;
    }

    void removeObserver(size_t id)
    {
        _observers.erase(std::remove_if(_observers.begin(),
                                        _observers.end(),
                                        [id](const Observer_t& observer) {
                                            return observer.id == id;
                                        }),
                         _observers.end());
    }

    void clearObservers()
    {
        _observers.clear();
    }

private:
    struct Observer_t {
        size_t id = 0;
        void* context = nullptr;
        OnChangedCallback callback = nullptr;
    };

    T _value;
    std::vector<Observer_t> _observers;
    size_t _last_id = 0;

    void notify()
    {
        for (auto& observer : _observers) {
            if (observer.callback) {
                observer.callback(observer.context, _value);
            }
        }
    }
};

} // namespace smooth_ui_toolkit
