/**
 * @file ring_buffer.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <cstddef>
#include <functional>
#include <memory>
// Refs:
// https://en.wikipedia.org/wiki/Circular_buffer

namespace smooth_ui_toolkit {

/**
 * @brief
 *
 * @tparam T
 * @tparam Capacity
 */
template <typename T, size_t Capacity>
class RingBuffer {
public:
    RingBuffer() : _buffer(std::make_unique<T[]>(Capacity)) {}

    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;

    ~RingBuffer() = default;

    void setAllowOverwrite(bool allowOverwrite)
    {
        _allow_overwrite = allowOverwrite;
    }

    constexpr size_t capacity() const
    {
        return Capacity;
    }
    size_t size() const
    {
        return _current_size;
    }
    bool empty() const
    {
        return _current_size == 0;
    }
    bool full() const
    {
        return _current_size == Capacity;
    }

    void clear()
    {
        _w_index = 0;
        _r_index = 0;
        _current_size = 0;
    }

    void push(const T& value)
    {
        if (full()) {
            if (_allow_overwrite) {
                _r_index = (_r_index + 1) % Capacity;
            } else {
                return;
            }
        } else {
            _current_size++;
        }

        _buffer[_w_index] = value;
        _w_index = (_w_index + 1) % Capacity;
    }

    void pop()
    {
        if (empty()) {
            return;
        }
        _r_index = (_r_index + 1) % Capacity;
        _current_size--;
    }

    T& front()
    {
        return _buffer[_r_index];
    }
    const T& front() const
    {
        return _buffer[_r_index];
    }

    T& back()
    {
        size_t last_idx = (_w_index == 0) ? (Capacity - 1) : (_w_index - 1);
        return _buffer[last_idx];
    }

    void popAll(std::function<void(T&)> onValue)
    {
        while (!empty()) {
            onValue(front());
            pop();
        }
    }

    void peekAll(std::function<void(const T&, bool& stopPeeking)> onValue) const
    {
        size_t count = _current_size;
        size_t peek_idx = _r_index;
        bool stop_peeking = false;

        for (size_t i = 0; i < count; ++i) {
            onValue(_buffer[peek_idx], stop_peeking);
            if (stop_peeking) {
                break;
            }
            peek_idx = (peek_idx + 1) % Capacity;
        }
    }

    T* rawBuffer()
    {
        return _buffer.get();
    }
    const T* rawBuffer() const
    {
        return _buffer.get();
    }

    size_t readIndex() const
    {
        return _r_index;
    }
    size_t writeIndex() const
    {
        return _w_index;
    }

private:
    std::unique_ptr<T[]> _buffer;
    size_t _w_index = 0;
    size_t _r_index = 0;
    size_t _current_size = 0;
    bool _allow_overwrite = true;
};

} // namespace smooth_ui_toolkit