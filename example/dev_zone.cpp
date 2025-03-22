/**
 * @file dev_zone.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <smooth_ui_toolkit.h>
#include <mooncake_log.h>
#include "animation/animate_value/animate_value.h"
#include "lvgl/lvgl_cpp/obj.h"
#include "utils/raylib_wrapper.h"
#include "utils/lvgl_wrapper.h"
#include <lvgl/lvgl_cpp/label.h>
#include <lvgl/lvgl_cpp/slider.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <lvgl/lvgl_cpp/button.h>
#include <string>
#include <vector>
#include <array>

using namespace smooth_ui_toolkit;
using namespace lvgl_cpp;

class DigitFlow : public LvObject {
public:
    DigitFlow(lv_obj_t* parent = nullptr)
    {
        _lv_obj = lv_obj_create(parent);
        lv_obj_null_on_delete(&_lv_obj);
    }

    virtual ~DigitFlow() {};

    inline void init()
    {
        // Mask basic
        setPadding(0, 0, 0, 0);
        setOutlineWidth(0);
        setRadius(0);
        setBorderWidth(0);
        removeFlag(LV_OBJ_FLAG_SCROLLABLE);
        setBgOpa(LV_OPA_TRANSP);

        // Child labels
        _digit_labels.clear();
        _digit_labels.resize(12);
        for (int i = 0; i < 12; i++) {
            _digit_labels[i] = std::make_unique<LvLabel>(_lv_obj);
            _digit_labels[i]->setText(std::to_string(_digit_list[i]));
            _digit_labels[i]->setAlign(LV_ALIGN_CENTER);
        }

        // Font height
        _font_height = lv_font_get_line_height(getTextFont());
        _digit_y_offset = _current_digit_index * _font_height;
        setSize(LV_SIZE_CONTENT, _font_height);
    }

    inline void setTextFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        LvObject::setTextFont(font, selector);
        init();
    }

    inline void update()
    {
        if (_font_height <= 0) {
            init();
        }
        _digit_y_offset.update();
        for (int i = 0; i < _digit_labels.size(); i++) {
            _digit_labels[i]->setPos(0, i * _font_height - _digit_y_offset.directValue());
        }
    }

    inline int value()
    {
        return _digit_list[_current_digit_index];
    }

    inline void increase()
    {
        if (_current_digit_index >= _digit_list.size() - 2) {
            _current_digit_index = 1;
            _digit_y_offset.retarget(0, 1 * _font_height);
        } else {
            _current_digit_index++;
            _digit_y_offset = _current_digit_index * _font_height;
        }
    }

    inline void decrease()
    {
        if (_current_digit_index <= 1) {
            _current_digit_index = _digit_list.size() - 2;
            _digit_y_offset.retarget((_digit_list.size() - 1) * _font_height, _current_digit_index * _font_height);
        } else {
            _current_digit_index--;
            _digit_y_offset = _current_digit_index * _font_height;
        }
    }

    inline void increaseTo(int targetValue)
    {
        increase();
        int target_digit = std::abs(targetValue) % 10;
        while (value() != target_digit) {
            increase();
        }
    }

    inline void decreaseTo(int targetValue)
    {
        decrease();
        int target_digit = std::abs(targetValue) % 10;
        while (value() != target_digit) {
            decrease();
        }
    }

    inline AnimateValue& flowAnimate()
    {
        return _digit_y_offset;
    }

protected:
    static inline constexpr std::array<int, 12> _digit_list = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int32_t _font_height = 0;
    AnimateValue _digit_y_offset;
    size_t _current_digit_index = 1;
    std::vector<std::unique_ptr<LvLabel>> _digit_labels;
};

int main()
{
    lvgl::create_window(800, 520);

    auto digit_flow = new DigitFlow(lv_screen_active());
    digit_flow->setPos(500, 100);
    // digit_flow->setPos(0, 0);
    digit_flow->setTextFont(&lv_font_montserrat_48);

    auto btn_next = new LvButton(lv_screen_active());
    btn_next->setPos(100, 100);
    btn_next->label().setText("-1");
    btn_next->onClick().connect([&]() { digit_flow->decrease(); });

    auto btn_last = new LvButton(lv_screen_active());
    btn_last->setPos(100, 200);
    btn_last->label().setText("+1");
    btn_last->onClick().connect([&]() { digit_flow->increase(); });

    int target_value = 0;
    auto slider = new LvSlider(lv_screen_active());
    slider->setPos(100, 300);
    slider->setRange(-100, 100);
    slider->onValueChanged().connect([&](int value) {
        if (value > target_value) {
            digit_flow->increaseTo(value);
        } else {
            digit_flow->decreaseTo(value);
        }
        target_value = value;
    });

    while (1) {
        digit_flow->update();
        lvgl::update_window();
    }

    return 0;
}
