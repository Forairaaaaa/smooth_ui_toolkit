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

class LvButton : public LvObject {
public:
    LvButton(lv_obj_t* parent = nullptr)
    {
        _lv_obj = lv_button_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~LvButton() {};

    LvLabel& label()
    {
        if (!_label) {
            _label = std::make_unique<LvLabel>(_lv_obj);
        }
        return *_label;
    }

protected:
    std::unique_ptr<LvLabel> _label;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit
