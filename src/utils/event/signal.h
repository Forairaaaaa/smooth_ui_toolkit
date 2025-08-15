/**
 * @file signal.h
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
#include <vector>
#include <mutex>
#include <algorithm>

namespace smooth_ui_toolkit {

/**
 * @brief Observer pattern like godot's signal
 *
 * @tparam T
 */
template <typename... Args>
class Signal {
public:
    using SlotType = std::function<void(Args...)>;

    size_t connect(const SlotType& slot)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        size_t id = ++_last_id;
        _slots.push_back({id, slot});
        return id;
    }

    void disconnect(size_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots.erase(std::remove_if(_slots.begin(),
                                    _slots.end(),
                                    [id](auto& pair) {
                                        return pair.first == id;
                                    }),
                     _slots.end());
    }

    void emit(Args... args)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto& [id, slot] : _slots) {
            slot(args...);
        }
    }

private:
    std::vector<std::pair<size_t, SlotType>> _slots;
    size_t _last_id = 0;
    std::mutex _mutex;
};

template <>
class Signal<void> : public Signal<> {};

} // namespace smooth_ui_toolkit
