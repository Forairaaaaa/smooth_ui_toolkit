/**
 * @file number_flow_float.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-07-26
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://number-flow.barvian.me
#pragma once
#include "../lvgl_cpp/obj.hpp"
#include "number_flow.hpp"
#include <lvgl.h>
#include <memory>
#include <cmath>
#include <string>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

class NumberFlowFloat : public Widget<lv_obj_create> {
public:
    using Widget::Widget;

    // no copy constructor and copy assignment operator
    NumberFlowFloat(const NumberFlowFloat&) = delete;
    NumberFlowFloat& operator=(const NumberFlowFloat&) = delete;

    // Spring will feels more natural
    animation_type::Type_t animationType = animation_type::spring;
    bool transparentBg = true;
    bool showPositiveSign = false;
    int decimalPlaces = 2; // 小数位数

    void init()
    {
        // Mask basic
        setPadding(0, 0, 0, 0);
        removeFlag(LV_OBJ_FLAG_SCROLLABLE);
        if (transparentBg) {
            setOutlineWidth(0);
            setBorderWidth(0);
            setBgOpa(LV_OPA_TRANSP);
        }

        // Font height and width
        _font_height = lv_font_get_line_height(getTextFont());
        _font_width = lv_font_get_glyph_width(getTextFont(), '0', '0');

        setSize(LV_SIZE_CONTENT, _font_height);

        // Create integer part
        if (!_integer_flow) {
            _integer_flow = std::make_unique<NumberFlow>(this->raw_ptr());
            _integer_flow->animationType = animationType;
            _integer_flow->transparentBg = true;
            _integer_flow->showPositiveSign = showPositiveSign;
            // 先设置前后缀，再调用 init
            _integer_flow->setPrefix(_prefix);
            _integer_flow->setSuffix("."); // 整数部分后缀为小数点
            _integer_flow->init();
        }

        // Create decimal part
        if (!_decimal_flow) {
            _decimal_flow = std::make_unique<NumberFlow>(this->raw_ptr());
            _decimal_flow->animationType = animationType;
            _decimal_flow->transparentBg = true;
            _decimal_flow->showPositiveSign = false;  // 小数部分不显示符号
            _decimal_flow->minDigits = decimalPlaces; // 设置最小位数，确保前导零
            // 先设置后缀，再调用 init
            _decimal_flow->setSuffix(_suffix);
            _decimal_flow->init();
        }

        // 设置初始值
        if (_current_value != 0.0f || !_is_initialized) {
            setValue(_current_value);
            _is_initialized = true;
        }
    }

    void update()
    {
        if (!_integer_flow || !_decimal_flow) {
            init();
            return;
        }

        _integer_flow->update();
        _decimal_flow->update();

        updateLayout();
    }

    float value() const
    {
        return _current_value;
    }

    void setValue(float targetValue)
    {
        _current_value = targetValue;

        if (!_integer_flow || !_decimal_flow) {
            init();
            return;
        }

        // 分离整数和小数部分
        int integer_part = static_cast<int>(targetValue);
        float decimal_part = std::abs(targetValue - integer_part);

        // 计算小数部分的整数表示
        int decimal_multiplier = static_cast<int>(std::pow(10, decimalPlaces));
        int decimal_int = static_cast<int>(std::round(decimal_part * decimal_multiplier));

        // 处理进位情况
        if (decimal_int >= decimal_multiplier) {
            integer_part += (targetValue >= 0) ? 1 : -1;
            decimal_int = 0;
        }

        _integer_flow->setValue(integer_part);
        _decimal_flow->setValue(decimal_int);

        updateLayout();
    }

    void setPrefix(const std::string& newPrefix)
    {
        _prefix = newPrefix;
        if (_integer_flow) {
            _integer_flow->setPrefix(_prefix);
        }
    }

    void setSuffix(const std::string& newSuffix)
    {
        _suffix = newSuffix;
        if (_decimal_flow) {
            _decimal_flow->setSuffix(_suffix);
        }
    }

    void setDecimalPlaces(int places)
    {
        decimalPlaces = places;
        if (_decimal_flow) {
            _decimal_flow->minDigits = decimalPlaces;
        }
    }

    // 设置前缀颜色
    void setPrefixColor(lv_color_t color)
    {
        if (_integer_flow) {
            _integer_flow->setPrefixColor(color);
        }
    }

    // 设置后缀颜色
    void setSuffixColor(lv_color_t color)
    {
        if (_decimal_flow) {
            _decimal_flow->setSuffixColor(color);
        }
    }

    // 设置数字颜色
    void setDigitColor(lv_color_t color)
    {
        if (_integer_flow) {
            _integer_flow->setDigitColor(color);
        }
        if (_decimal_flow) {
            _decimal_flow->setDigitColor(color);
        }
    }

    int getTotalWidth()
    {
        if (!_integer_flow || !_decimal_flow)
            return 0;

        int integer_width = _integer_flow->getTotalWidth();
        int decimal_width = _decimal_flow->getTotalWidth();
        return integer_width + decimal_width;
    }

protected:
    float _current_value = 0.0f;
    int32_t _font_height = 0;
    int32_t _font_width = 0;
    bool _is_initialized = false;
    std::string _prefix = "";
    std::string _suffix = "";

    std::unique_ptr<NumberFlow> _integer_flow;
    std::unique_ptr<NumberFlow> _decimal_flow;

    void updateLayout()
    {
        if (!_integer_flow || !_decimal_flow) {
            return;
        }

        // 整数部分位置
        _integer_flow->setPos(0, 0);

        // 小数部分位置 (紧跟在整数部分后面)
        int integer_width = _integer_flow->getTotalWidth();
        _decimal_flow->setPos(integer_width, 0);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit