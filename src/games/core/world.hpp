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

namespace smooth_ui_toolkit::games {

class World {
public:
    GameObject* createObject(std::unique_ptr<GameObject> obj)
    {
        int id = _objects.create(std::move(obj));
        GameObject* go = _objects.get(id);
        _pending_init.push_back(go);
        return go;
    }

    void init() {}

    void update(float dt)
    {
        // Init pending objects
        if (!_pending_init.empty()) {
            for (auto* obj : _pending_init) {
                obj->onInit();
            }
            _pending_init.clear();
        }

        // Update objects
        _objects.forEach([&](GameObject* obj, int) {
            obj->update(dt);
        });

        // Update systems
        _area_system.update(get_object_list());

        // Cleanup destroyed objects
        cleanup();
    }

    void forEach(const std::function<void(GameObject*)>& func)
    {
        _objects.forEach([&](GameObject* obj, int) {
            func(obj);
        });
    }

private:
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

} // namespace smooth_ui_toolkit::games
