/**
 * @file world.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "game_object.hpp"
#include "system/area_system.hpp"
#include "core/hal/hal.hpp"

namespace smooth_ui_toolkit::games::engine {

class World {
public:
    GameObject* createObject(std::unique_ptr<GameObject> obj)
    {
        int id = _objects.create(std::move(obj));
        GameObject* go = _objects.get(id);
        _pending_init.push_back(go);
        return go;
    }

    void init()
    {
        _last_tick = ui_hal::get_tick_s();
    }

    void update()
    {
        // Init pending objects
        if (!_pending_init.empty()) {
            for (auto* obj : _pending_init) {
                obj->onInit();
            }
            _pending_init.clear();
        }

        // Update objects
        _current_tick = ui_hal::get_tick_s();
        _delta_time = _current_tick - _last_tick;
        _last_tick = _current_tick;
        _objects.forEach([&](GameObject* obj, int) {
            obj->update(_delta_time);
        });

        // Update systems
        _area_system.update(get_object_list());

        // Cleanup destroyed objects
        cleanup();
    }

private:
    float _current_tick = 0.0f;
    float _last_tick = 0.0f;
    float _delta_time = 0.0f;

    ObjectPool<GameObject> _objects;
    std::vector<GameObject*> _pending_init;

    std::vector<GameObject*> _system_object_list_cache;
    AreaSystem _area_system;

    std::vector<GameObject*>& get_object_list()
    {
        _system_object_list_cache.clear();
        _objects.forEach([&](GameObject* obj, int) {
            _system_object_list_cache.push_back(obj);
        });
        return _system_object_list_cache;
    }

    void cleanup()
    {
        _objects.forEach([&](GameObject* obj, int) {
            if (obj->isDestroyRequested()) {
                obj->onDestroy();
            }
        });

        _area_system.handlePreDestroy(_objects);

        _objects.cleanup();
    }
};

} // namespace smooth_ui_toolkit::games::engine
