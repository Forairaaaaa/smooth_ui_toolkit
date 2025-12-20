/**
 * @file game_object.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "game_object.hpp"
#include "components/transform.hpp"
#include "components/shape.hpp"
#include <cassert>

namespace smooth_ui_toolkit::games {

void GameObject::add(std::unique_ptr<Component> comp)
{
    if (comp->type() == ComponentType::Shape) {
        assert(get<Transform>() && "Shape requires Transform");
    }

    if (comp->type() == ComponentType::Area) {
        assert(get<Shape>() && "Area requires Shape");
    }

    comp->owner = this;
    components.push_back(std::move(comp));
}

} // namespace smooth_ui_toolkit::games
