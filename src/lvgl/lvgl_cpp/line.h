/**
 * @file line.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "obj.h"
#include <lvgl.h>
#include <cstdint>
#include <vector>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl line
 *
 */
class Line : public Widget<lv_line_create> {
public:
    using Widget::Widget;

    void setPoints(const std::vector<lv_point_precise_t>& points)
    {
        lv_line_set_points(this->raw_ptr(), points.data(), points.size());
    }

    void setPoints(const lv_point_precise_t* points, uint32_t point_num)
    {
        lv_line_set_points(this->raw_ptr(), points, point_num);
    }

    uint32_t getPointCount()
    {
        return lv_line_get_point_count(this->raw_ptr());
    }

    void setLineColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_line_color(this->raw_ptr(), color, selector);
    }

    void setLineDashGap(int32_t gap, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_line_dash_gap(this->raw_ptr(), gap, selector);
    }

    void setLineDashWidth(int32_t width, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_line_dash_width(this->raw_ptr(), width, selector);
    }

    void setLineOpa(lv_opa_t opa, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_line_opa(this->raw_ptr(), opa, selector);
    }

    void setLineRounded(bool rounded, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_line_rounded(this->raw_ptr(), rounded, selector);
    }

    void setLineWidth(int32_t width, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_line_width(this->raw_ptr(), width, selector);
    }
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit