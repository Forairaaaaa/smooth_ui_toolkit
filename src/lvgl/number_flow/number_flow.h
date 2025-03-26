/**
 * @file number_flow.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://number-flow.barvian.me
#pragma once
#include "../lvgl_cpp/obj.h"
#include "../lvgl_cpp/label.h"
#include "../../animation/animate_value/animate_value.h"
#include <lvgl.h>
#include <vector>
#include <memory>
#include <array>
#include <cmath>
#include <algorithm>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class DigitFlow : public LvObject {
public:
    DigitFlow() : LvObject() {}
    DigitFlow(lv_obj_t* parent) : LvObject(parent) {}

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
        _digit_labels.resize(_digit_list.size());
        for (int i = 0; i < _digit_list.size(); i++) {
            _digit_labels[i].create(_lv_obj.get());
            _digit_labels[i].setText(std::to_string(_digit_list[i]));
            _digit_labels[i].setAlign(LV_ALIGN_CENTER);
        }

        // Font height
        _font_height = lv_font_get_line_height(getTextFont());
        _digit_y_offset.springOptions().visualDuration = 0.6;
        _digit_y_offset.springOptions().bounce = 0.05;
        _digit_y_offset = _current_digit_index * _font_height;
        setSize(LV_SIZE_CONTENT, _font_height);
    }

    inline void setTextFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        LvObject::setTextFont(font, selector);
        init();
    }

    inline void setTextColor(lv_color_t color)
    {
        LvObject::setTextColor(color);
        for (auto& digit : _digit_labels) {
            digit.setTextColor(color);
        }
    }

    inline void update()
    {
        if (_font_height <= 0) {
            init();
        }
        _digit_y_offset.update();
        for (int i = 0; i < _digit_labels.size(); i++) {
            _digit_labels[i].setPos(0, i * _font_height - _digit_y_offset.directValue());
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
    std::vector<LvLabel> _digit_labels;
};

class NumberFlow : public LvObject {
public:
    struct Item_t {
        AnimateValue positionX;
        AnimateValue opacity;
        bool isGoingDestroy = false;
    };

    struct Digit_t : public Item_t {
        DigitFlow digitFlow;
    };

    struct Label_t : public Item_t {
        std::unique_ptr<LvLabel> label;
    };

    NumberFlow(lv_obj_t* parent) : LvObject(parent) {}
    virtual ~NumberFlow() {};

    bool transparentBg = true;
    bool showPositiveSign = false;

    inline void init()
    {
        // Mask basic
        setPadding(0, 0, 0, 0);
        removeFlag(LV_OBJ_FLAG_SCROLLABLE);
        if (transparentBg) {
            setOutlineWidth(0);
            setBorderWidth(0);
            setBgOpa(LV_OPA_TRANSP);
        }

        // Font height
        _font_height = lv_font_get_line_height(getTextFont());
        _font_width = lv_font_get_glyph_width(getTextFont(), '0', '0');
        setSize(LV_SIZE_CONTENT, _font_height);

        setValue(_current_number);
    }

    inline void update()
    {
        if (_digits.empty()) {
            init();
        }

        handle_sign_update();
        handle_digit_update();
    }

    inline int value()
    {
        return _current_number;
    }

    inline void setValue(int targetValue)
    {
        _current_number = targetValue;
        handle_sign_changed();
        handle_digit_changed();
        handle_digit_number_changed();
    }

protected:
    int32_t _font_height = 0;
    int32_t _font_width = 0;
    int _last_number = 0;
    int _current_number = 0;
    int _current_number_of_digits = 1;
    std::vector<Digit_t> _digits;
    std::unique_ptr<Label_t> _sign;

    inline int get_number_of_digits(int num)
    {
        if (num == 0) {
            return 1;
        }
        int count = 0;
        while (num != 0) {
            num /= 10;
            count++;
        }
        return count;
    }

    inline void handle_digit_changed()
    {
        auto new_number_of_digits = get_number_of_digits(_current_number);
        int digit_list_size = _digits.size();

        // Add digits
        if (new_number_of_digits > digit_list_size) {
            // mclog::info("add digits");
            while (new_number_of_digits > digit_list_size) {
                _digits.push_back(Digit_t());
                _digits.back().digitFlow.create(_lv_obj.get());
                _digits.back().digitFlow.init();
                _digits.back().digitFlow.setTextColor(getTextColor());
                _digits.back().positionX.springOptions().visualDuration = 0.6;
                _digits.back().positionX.springOptions().bounce = 0.05;
                if (digit_list_size != 0) {
                    _digits.back().positionX.teleport((_current_number_of_digits - 1) * _font_width);
                }
                _digits.back().positionX.move(digit_list_size * _font_width);
                _digits.back().opacity.springOptions().visualDuration = 0.3;
                _digits.back().opacity.springOptions().bounce = 0.05;
                _digits.back().opacity.move(255);
                digit_list_size++;
            }
        }

        // Remove digits
        else if ((new_number_of_digits < digit_list_size) && (new_number_of_digits < _current_number_of_digits)) {
            // mclog::info("remove digits");
            if (_current_number_of_digits > new_number_of_digits) {
                // move extra digits back to 0, and mark destroy
                for (int i = new_number_of_digits; i < digit_list_size; i++) {
                    _digits[i].positionX.move((new_number_of_digits - 1) * _font_width);
                    _digits[i].opacity = 0;
                    _digits[i].opacity.move(0);
                    _digits[i].isGoingDestroy = true;
                }
            }
        }

        // Reorder digits
        int sign_width = 0;
        if (_sign) {
            if (!_sign->isGoingDestroy) {
                sign_width = lv_font_get_glyph_width(getTextFont(), _current_number < 0 ? '-' : '+', '0');
            }
        }
        for (int i = 0; i < new_number_of_digits; i++) {
            _digits[i].positionX.move(i * _font_width + sign_width);
            _digits[i].opacity.move(255);
            _digits[i].isGoingDestroy = false;
        }

        _current_number_of_digits = new_number_of_digits;
    }

    inline void handle_digit_update()
    {
        for (int i = 0; i < _digits.size(); i++) {
            if (_digits[i].isGoingDestroy && _digits[i].positionX.done() && _digits[i].opacity.done()) {
                _digits.erase(_digits.begin() + i);
            }
        }

        for (auto& digit : _digits) {
            digit.digitFlow.update();
            digit.digitFlow.setPos(digit.positionX, 0);
            digit.digitFlow.setOpa(std::clamp((int)digit.opacity.value(), 0, 255));
        }
    }

    inline void handle_digit_number_changed()
    {
        // Iterate through each digit
        int number = _current_number;
        int divisor = std::pow(10, _current_number_of_digits - 1);
        for (int i = 0; i < _current_number_of_digits; ++i) {
            int digit = std::abs(number / divisor);
            // mclog::info("{}", digit);
            if (_digits[i].digitFlow.value() != digit) {
                bool increase = (_last_number < _current_number);
                if (_current_number < 0) {
                    increase = !increase;
                }
                if (increase) {
                    _digits[i].digitFlow.increaseTo(digit);
                } else {
                    _digits[i].digitFlow.decreaseTo(digit);
                }
            }
            number %= divisor;
            divisor /= 10;
        }
        _last_number = _current_number;
    }

    inline void handle_sign_changed()
    {
        std::string new_sign;
        if (_current_number < 0) {
            new_sign = "-";
        } else if (_current_number > 0) {
            new_sign = showPositiveSign ? "+" : "";
        }

        if (new_sign.empty()) {
            if (_sign) {
                _sign->isGoingDestroy = true;
                _sign->positionX.move(0);
                _sign->opacity.move(0);
            }
        } else {
            if (!_sign) {
                _sign = std::make_unique<Label_t>();
                _sign->label = std::make_unique<LvLabel>(_lv_obj.get());
            }
            _sign->positionX.move(0);
            if (_sign->label->getText() != new_sign) {
                _sign->opacity.teleport(0);
            }
            _sign->opacity.move(255);
            _sign->isGoingDestroy = false;
            _sign->label->setText(new_sign);
        }
    }

    inline void handle_sign_update()
    {
        if (_sign) {
            _sign->positionX.update();
            _sign->opacity.update();
            _sign->label->setPos(0, _sign->positionX);
            _sign->label->setOpa(std::clamp((int)_sign->opacity.value(), 0, 255));
            if (_sign->isGoingDestroy && _sign->positionX.done() && _sign->opacity.done()) {
                _sign.reset();
            }
        }
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit