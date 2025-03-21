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

    void emit(Args... args)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto& slot : _slots) {
            slot(args...);
        }
    }

    void connect(const SlotType& slot)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots.push_back(slot);
    }

    void disconnect(const SlotType& slot)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots.erase(std::remove(_slots.begin(), _slots.end(), slot), _slots.end());
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots.clear();
    }

private:
    std::vector<SlotType> _slots;
    std::mutex _mutex;
};

template <>
class Signal<void> : public Signal<> {
};

} // namespace smooth_ui_toolkit
