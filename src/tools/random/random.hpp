/**
 * @file random.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <mutex>
#include <random>
#include <vector>
#include <cassert>

#ifdef ESP_PLATFORM
#include <esp_random.h>
#endif

namespace smooth_ui_toolkit {

class Random {
public:
    static Random& getInstance()
    {
        static Random instance;
        return instance;
    }

    int getInt(int a, int b)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (a > b) {
            std::swap(a, b);
        }
        return std::uniform_int_distribution<int>{a, b}(_rng);
    }

    double getDouble(double a, double b)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (a > b) {
            std::swap(a, b);
        }
        return std::uniform_real_distribution<double>{a, b}(_rng);
    }

    template <typename T>
    const T& choice(const std::vector<T>& vec)
    {
        assert(!vec.empty());
        std::lock_guard<std::mutex> lock(_mutex);
        std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
        return vec[dist(_rng)];
    }

private:
    std::mt19937 _rng;
    std::mutex _mutex;

    Random()
    {
#ifdef ESP_PLATFORM
        rng.seed(esp_random());
#else
        std::random_device rd;
        _rng.seed(rd());
#endif
    }
};

} // namespace smooth_ui_toolkit
