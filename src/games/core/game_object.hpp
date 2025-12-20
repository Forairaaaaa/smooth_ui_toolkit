/**
 * @file game_object.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "tools/object_pool/object_pool.hpp"
#include "components/component.hpp"
#include <cassert>
#include <vector>
#include <memory>

namespace smooth_ui_toolkit::games {

class GameObject : public Poolable {
public:
    int groupId = 0;

    template <typename T>
    T* get()
    {
        constexpr ComponentType type = T::Type;
        for (auto& comp : components) {
            if (comp->type() == type) {
                return static_cast<T*>(comp.get());
            }
        }
        return nullptr;
    }

    void add(std::unique_ptr<Component> comp);

    void update(float dt)
    {
        for (auto& comp : components) {
            comp->update(dt);
        }
        onUpdate(dt);
    }

    // Lifecycle
    virtual void onReady() {}
    virtual void onUpdate(float dt) {}
    virtual void onDestroy() {}

private:
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace smooth_ui_toolkit::games
