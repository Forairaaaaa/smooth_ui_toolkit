/**
 * @file single_observable.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2026-06-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once
#include <utility>

namespace smooth_ui_toolkit {

/**
 * @brief Observable value with only one observer, no mutex.
 *
 * @tparam T
 */
template <typename T>
class SingleObservable {
public:
    using OnChangedCallback = void (*)(void* context, const T& newValue);

    explicit SingleObservable(T defaultValue) : _value(std::move(defaultValue)) {}

    SingleObservable(const SingleObservable&) = delete;
    SingleObservable& operator=(const SingleObservable&) = delete;
    SingleObservable(SingleObservable&&) = delete;
    SingleObservable& operator=(SingleObservable&&) = delete;

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

    void observe(void* context, OnChangedCallback callback)
    {
        _context = context;
        _callback = callback;
        notify();
    }

    void removeObserver()
    {
        _context = nullptr;
        _callback = nullptr;
    }

private:
    T _value;
    void* _context = nullptr;
    OnChangedCallback _callback = nullptr;

    void notify()
    {
        if (_callback) {
            _callback(_context, _value);
        }
    }
};

} // namespace smooth_ui_toolkit
