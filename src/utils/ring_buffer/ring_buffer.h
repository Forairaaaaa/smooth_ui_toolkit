/**
 * @file ring_buffer.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstddef>
#include <functional>
// Refs:
// https://en.wikipedia.org/wiki/Circular_buffer

namespace SmoothUIToolKit
{
    template <typename T, size_t Capacity>
    class RingBuffer
    {
    public:
        struct Config_t
        {
            bool allowOverwrite = true;
        };

    private:
        struct Data_t
        {
            T* buffer = nullptr;
            size_t w_index = 0;
            size_t r_index = 0;
            size_t capacity = Capacity;
        };
        Data_t _data;
        Config_t _config;

    public:
        RingBuffer() { _data.buffer = new T[Capacity]; }
        ~RingBuffer() { delete _data.buffer; }

        inline Config_t& setConfig() { return _config; }
        inline const Config_t& getConfig() { return _config; }

        inline void allowOverwrite(bool allow) { _config.allowOverwrite = allow; }

        inline bool isFull() { return (_data.w_index + 1) % _data.capacity == _data.r_index; }
        inline bool isEmpty() { return _data.r_index == _data.w_index; }

        inline size_t size() { return _data.capacity; }
        inline void reSize(size_t capacity)
        {
            if (_data.capacity == capacity)
                return;

            _data.capacity = capacity;
            delete _data.buffer;
            _data.buffer = new T[_data.capacity];
        }

        bool put(const T& value)
        {
            if (isFull())
            {
                // If allow overwrite, push read index
                if (_config.allowOverwrite)
                    _data.r_index = (_data.r_index + 1) % _data.capacity;
                else
                    return false;
            }

            _data.buffer[_data.w_index] = value;
            _data.w_index = (_data.w_index + 1) % _data.capacity;
            return true;
        }

        bool get(T& value)
        {
            if (isEmpty())
                return false;

            value = _data.buffer[_data.r_index];
            _data.r_index = (_data.r_index + 1) % _data.capacity;
            return true;
        }

        bool getAll(std::function<void(T)> valueCallback)
        {
            if (isEmpty())
                return false;

            T temp;
            while (!isEmpty())
            {
                get(temp);
                valueCallback(temp);
            }
            return true;
        }

        bool peek(T& value)
        {
            if (isEmpty())
                return false;

            value = _data.buffer[_data.r_index];
            return true;
        }

        bool peekAll(std::function<void(const T&)> valueCallback)
        {
            if (isEmpty())
                return false;

            size_t peek_index = _data.r_index;
            while (peek_index != _data.w_index)
            {
                valueCallback(_data.buffer[peek_index]);
                peek_index = (peek_index + 1) % _data.capacity;
            }
            return true;
        }

        bool peekAllWithBreak(std::function<void(const T&, bool& stopPeeking)> valueCallback)
        {
            if (isEmpty())
                return false;

            size_t peek_index = _data.r_index;
            bool stop_peeking = false;
            while (peek_index != _data.w_index)
            {
                valueCallback(_data.buffer[peek_index], stop_peeking);
                peek_index = (peek_index + 1) % _data.capacity;

                if (stop_peeking)
                    break;
            }
            return true;
        }

        size_t valueNum()
        {
            if (isFull())
                return _data.capacity;
            if (isEmpty())
                return 0;

            if (_data.r_index < _data.w_index)
                return _data.w_index - _data.r_index;
            else
                return _data.capacity - _data.r_index + _data.w_index;
        }

        const T* rawBuffer() { return _data.buffer; }

        const size_t& readIndex() { return _data.r_index; }

        const size_t& writeIndex() { return _data.w_index; }

        const T& lastValue()
        {
            if (_data.w_index == 0)
                return _data.buffer[_data.capacity - 1];
            else
                return _data.buffer[_data.w_index - 1];
        }
    };
} // namespace SmoothUIToolKit
