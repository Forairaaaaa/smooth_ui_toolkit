/**
 * @file digit_flow.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://number-flow.barvian.me
#pragma once
#include "lvgl/lvgl_cpp/obj.hpp"
#include "lvgl/lvgl_cpp/label.hpp"
#include "core/animation/animate_value/animate_value.hpp"
#include <lvgl.h>
#include <vector>
#include <memory>
#include <array>
#include <cmath>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class DigitFlow : public Widget<lv_obj_create> {
public:
    using Widget::Widget;

    // no copy constructor and copy assignment operator
    DigitFlow(const DigitFlow&) = delete;
    DigitFlow& operator=(const DigitFlow&) = delete;

    // Spring will feels more natural
    AnimationType animationType = AnimationType::Spring;

    static void setup_animation(AnimateValue& animateValue, AnimationType animationType)
    {
        if (animationType == AnimationType::Spring) {
            animateValue.springOptions().visualDuration = 0.6;
            animateValue.springOptions().bounce = 0.05;
        } else if (animationType == AnimationType::Easing) {
            animateValue.easingOptions().duration = 0.6;
            animateValue.easingOptions().easingFunction = ease::ease_out_quad;
        }
    }

    void init()
    {
        // Mask basic
        setPadding(0, 0, 0, 0);
        setOutlineWidth(0);
        setRadius(0);
        setBorderWidth(0);
        removeFlag(LV_OBJ_FLAG_SCROLLABLE);
        removeFlag(LV_OBJ_FLAG_CLICKABLE);
        setBgOpa(LV_OPA_TRANSP);

        // Child labels
        _digit_labels.clear();
        _digit_labels.resize(_digit_list.size());
        for (int i = 0; i < _digit_list.size(); i++) {
            _digit_labels[i] = std::make_unique<Label>(this->raw_ptr());
            _digit_labels[i]->setText(std::to_string(_digit_list[i]));
            _digit_labels[i]->setAlign(LV_ALIGN_CENTER);
        }

        // Font height
        _font_height = lv_font_get_line_height(getTextFont());
        setup_animation(_digit_y_offset, animationType);
        _digit_y_offset = _current_digit_index * _font_height;
        setSize(LV_SIZE_CONTENT, _font_height);
    }

    void setTextFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        Object::setTextFont(font, selector);
        init();
    }

    void setTextColor(lv_color_t color)
    {
        Object::setTextColor(color);
        for (auto& digit : _digit_labels) {
            digit->setTextColor(color);
        }
    }

    void update()
    {
        if (_font_height <= 0) {
            init();
        }
        _digit_y_offset.update();
        for (int i = 0; i < _digit_labels.size(); i++) {
            _digit_labels[i]->setPos(0, i * _font_height - _digit_y_offset.directValue());
        }
    }

    int value()
    {
        return _digit_list[_current_digit_index];
    }

    void increase()
    {
        if (_current_digit_index >= _digit_list.size() - 2) {
            _current_digit_index = 1;
            _digit_y_offset.retarget(0, 1 * _font_height);
        } else {
            _current_digit_index++;
            _digit_y_offset = _current_digit_index * _font_height;
        }
    }

    void decrease()
    {
        if (_current_digit_index <= 1) {
            _current_digit_index = _digit_list.size() - 2;
            _digit_y_offset.retarget((_digit_list.size() - 1) * _font_height, _current_digit_index * _font_height);
        } else {
            _current_digit_index--;
            _digit_y_offset = _current_digit_index * _font_height;
        }
    }

    void increaseTo(int targetValue)
    {
        increase();
        int target_digit = std::abs(targetValue) % 10;
        while (value() != target_digit) {
            increase();
        }
    }

    void decreaseTo(int targetValue)
    {
        decrease();
        int target_digit = std::abs(targetValue) % 10;
        while (value() != target_digit) {
            decrease();
        }
    }

    AnimateValue& flowAnimate()
    {
        return _digit_y_offset;
    }

protected:
    static inline constexpr std::array<int, 12> _digit_list = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int32_t _font_height = 0;
    AnimateValue _digit_y_offset;
    size_t _current_digit_index = 1;
    std::vector<std::unique_ptr<Label>> _digit_labels;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit