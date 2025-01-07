/**
 * @file ring_buffer.h
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

template <typename T, size_t Capacity>
class ring_buffer {
public:
    ring_buffer()
    {
        _data.buffer = std::make_unique<T[]>(Capacity);
    }
    ~ring_buffer()
    {
        _data.buffer.reset();
    }

    // Allow overwrite the oldest data when buffer is full
    void setAllowOverwrite(bool allowOverwrite)
    {
        _data.allow_overwrite = allowOverwrite;
    }

    size_t capacity()
    {
        return _data.capacity;
    }
    void resetCapacity(size_t capacity)
    {
        if (_data.capacity == capacity) {
            return;
        }
        _data.capacity = capacity;
        _data.buffer = std::make_unique<T[]>(_data.capacity);
    }

    bool full()
    {
        // return (_data.w_index + 1) % _data.capacity == _data.r_index;
        return _data.current_size == _data.capacity;
    }
    bool empty()
    {
        // return _data.r_index == _data.w_index;
        return _data.current_size == 0;
    }

    size_t size()
    {
        return _data.current_size;
    }

    void push(const T& value)
    {
        if (full()) {
            // If allow overwrite, push read index
            if (_data.allow_overwrite) {
                _data.r_index = (_data.r_index + 1) % _data.capacity;
            } else {
                return;
            }
        }
        _data.buffer[_data.w_index] = value;
        _data.w_index = (_data.w_index + 1) % _data.capacity;

        _data.current_size++;
        if (_data.current_size > _data.capacity) {
            _data.current_size = _data.capacity;
        }
    }

    void pop()
    {
        if (empty()) {
            return;
        }
        _data.r_index = (_data.r_index + 1) % _data.capacity;
        _data.current_size--;
    }

    const T& front()
    {
        return _data.buffer[_data.r_index];
    }
    const T& back()
    {
        if (_data.w_index == 0) {
            return _data.buffer[_data.capacity - 1];
        } else {
            return _data.buffer[_data.w_index - 1];
        }
    }

    void popAll(std::function<void(const T&)> onValue)
    {
        while (!empty()) {
            onValue(front());
            pop();
        }
    }

    void peekAll(std::function<void(const T&, bool& stopPeeking)> onValue)
    {
        if (empty()) {
            return;
        }
        size_t peek_index = _data.r_index;
        bool stop_peeking = false;
        while (peek_index != _data.w_index) {
            onValue(_data.buffer[peek_index], stop_peeking);
            peek_index = (peek_index + 1) % _data.capacity;
            if (stop_peeking) {
                break;
            }
        }
    }

    const T* rawBuffer() const
    {
        return _data.buffer;
    }

    const size_t& readIndex()
    {
        return _data.r_index;
    }

    const size_t& writeIndex()
    {
        return _data.w_index;
    }

    void clear()
    {
        _data.w_index = 0;
        _data.r_index = 0;
    }

private:
    struct Data_t {
        std::unique_ptr<T[]> buffer;
        size_t capacity = Capacity;
        size_t w_index = 0;
        size_t r_index = 0;
        size_t current_size = 0;
        bool allow_overwrite = true;
    };
    Data_t _data;
};

} // namespace smooth_ui_toolkit