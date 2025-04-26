/**
 * @file button.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.h"
#include "label.h"
#include <memory>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl button
 *
 */
class Button : public Widget<lv_button_create> {
public:
    using Widget::Widget;

    Label& label()
    {
        if (!_label) {
            _label = std::make_unique<Label>(this->raw_ptr());
            _label->align(LV_ALIGN_CENTER, 0, 0);
        }
        return *_label;
    }

protected:
    std::unique_ptr<Label> _label;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit
