/**
 * @file canvas.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

#if LV_USE_CANVAS

#include "obj.hpp"
#include <cstdint>
#include <vector>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/**
 * @brief Lvgl canvas
 *
 * Usage:
 * @code
 * canvas.createBuffer(320, 240);
 * canvas.fillBg(lv_color_white());
 *
 * lv_layer_t layer;
 * canvas.startDrawing(layer);
 *
 * canvas.drawRect(layer, 0, 0, 100, 100, lv_color_black());
 * canvas.drawCircle(layer, 50, 50, 20, lv_color_red());
 *
 * canvas.finishDrawing(layer);
 * @endcode
 */
class Canvas : public Widget<lv_canvas_create> {
public:
    using Widget::Widget;

    void createBuffer(uint32_t width, uint32_t height, lv_color_format_t colorFormat = LV_COLOR_FORMAT_RGB565)
    {
        _buffer.clear();
        _buffer.resize(LV_DRAW_BUF_SIZE(width, height, colorFormat));
        lv_canvas_set_buffer(this->raw_ptr(), _buffer.data(), width, height, colorFormat);
    }

    void releaseBuffer()
    {
        _buffer.clear();
    }

    void fillBg(lv_color_t color, lv_opa_t opa = LV_OPA_COVER)
    {
        lv_canvas_fill_bg(this->raw_ptr(), color, opa);
    }

    void startDrawing(lv_layer_t& layer)
    {
        lv_canvas_init_layer(this->raw_ptr(), &layer);
    }

    void finishDrawing(lv_layer_t& layer)
    {
        lv_canvas_finish_layer(this->raw_ptr(), &layer);
    }

    void drawRect(lv_layer_t& layer, const lv_draw_rect_dsc_t& dsc, const lv_area_t& coords)
    {
        lv_draw_rect(&layer, &dsc, &coords);
    }

    void drawRect(lv_layer_t& layer,
                  int32_t x,
                  int32_t y,
                  int32_t w,
                  int32_t h,
                  lv_color_t color,
                  lv_opa_t opa = LV_OPA_COVER,
                  int32_t radius = 0,
                  int32_t border_width = 0,
                  lv_color_t border_color = lv_color_black(),
                  lv_opa_t border_opa = LV_OPA_COVER)
    {
        lv_draw_rect_dsc_t dsc;
        lv_draw_rect_dsc_init(&dsc);
        dsc.bg_color = color;
        dsc.bg_opa = opa;
        dsc.radius = radius;
        dsc.border_width = border_width;
        dsc.border_color = border_color;
        dsc.border_opa = border_opa;

        lv_area_t coords;
        coords.x1 = x;
        coords.y1 = y;
        coords.x2 = x + w - 1;
        coords.y2 = y + h - 1;

        drawRect(layer, dsc, coords);
    }

    void drawCircle(lv_layer_t& layer,
                    int32_t x,
                    int32_t y,
                    int32_t r,
                    lv_color_t color,
                    lv_opa_t opa = LV_OPA_COVER,
                    int32_t border_width = 0,
                    lv_color_t border_color = lv_color_black(),
                    lv_opa_t border_opa = LV_OPA_COVER)
    {
        lv_draw_rect_dsc_t dsc;
        lv_draw_rect_dsc_init(&dsc);
        dsc.bg_color = color;
        dsc.bg_opa = opa;
        dsc.radius = LV_RADIUS_CIRCLE;
        dsc.border_width = border_width;
        dsc.border_color = border_color;
        dsc.border_opa = border_opa;

        lv_area_t coords;
        coords.x1 = x - r;
        coords.y1 = y - r;
        coords.x2 = x + r - 1;
        coords.y2 = y + r - 1;

        drawRect(layer, dsc, coords);
    }

    void drawLine(lv_layer_t& layer, const lv_draw_line_dsc_t& dsc)
    {
        lv_draw_line(&layer, &dsc);
    }

    void drawLine(lv_layer_t& layer,
                  int32_t x1,
                  int32_t y1,
                  int32_t x2,
                  int32_t y2,
                  int32_t width = 2,
                  lv_color_t color = lv_color_black(),
                  lv_opa_t opa = LV_OPA_COVER,
                  uint8_t round_start = 0,
                  uint8_t round_end = 0,
                  int32_t dash_width = 0,
                  int32_t dash_gap = 0)
    {
        lv_draw_line_dsc_t dsc;
        lv_draw_line_dsc_init(&dsc);
        dsc.color = color;
        dsc.width = width;
        dsc.round_end = round_end;
        dsc.round_start = round_start;
        dsc.p1.x = x1;
        dsc.p1.y = y1;
        dsc.p2.x = x2;
        dsc.p2.y = y2;
        dsc.dash_gap = dash_gap;
        dsc.dash_width = dash_width;
        dsc.opa = opa;
        drawLine(layer, dsc);
    }

protected:
    std::vector<uint8_t> _buffer;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
