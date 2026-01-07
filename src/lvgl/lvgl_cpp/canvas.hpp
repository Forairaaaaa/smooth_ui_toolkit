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
 * canvas.startDrawing();
 *
 * canvas.drawRect(0, 0, 100, 100, lv_color_black());
 * canvas.drawCircle(50, 50, 20, lv_color_red());
 *
 * canvas.finishDrawing();
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

    void startDrawing()
    {
        lv_canvas_init_layer(this->raw_ptr(), &_layer);
    }

    void finishDrawing()
    {
        lv_canvas_finish_layer(this->raw_ptr(), &_layer);
    }

    /**
     * @brief Get the internal layer object for raw lvgl drawing functions
     *
     * @return lv_layer_t&
     */
    lv_layer_t& layer()
    {
        return _layer;
    }

    void drawRect(const lv_draw_rect_dsc_t& dsc, const lv_area_t& coords)
    {
        lv_draw_rect(&_layer, &dsc, &coords);
    }

    void drawRect(int32_t x,
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

        drawRect(dsc, coords);
    }

    void drawCircle(int32_t x,
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

        drawRect(dsc, coords);
    }

    void drawLine(const lv_draw_line_dsc_t& dsc)
    {
        lv_draw_line(&_layer, &dsc);
    }

    void drawLine(int32_t x1,
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
        drawLine(dsc);
    }

    void drawTriangle(const lv_draw_triangle_dsc_t& dsc)
    {
        lv_draw_triangle(&_layer, &dsc);
    }

    void drawTriangle(const std::vector<lv_point_t>& points,
                      lv_color_t color,
                      lv_opa_t opa = LV_OPA_COVER,
                      lv_color_t bg_grad_color = lv_color_black(),
                      lv_grad_dir_t bg_grad_dir = LV_GRAD_DIR_NONE,
                      int32_t bg_grad_stop = 255)
    {
        if (points.size() < 3)
            return;
        lv_draw_triangle_dsc_t dsc;
        lv_draw_triangle_dsc_init(&dsc);
        dsc.color = color;
        dsc.opa = opa;

        dsc.grad.dir = bg_grad_dir;
        if (bg_grad_dir != LV_GRAD_DIR_NONE) {
            dsc.grad.stops_count = 2;
            dsc.grad.stops[0].color = color;
            dsc.grad.stops[0].frac = 0;
            dsc.grad.stops[0].opa = opa;

            dsc.grad.stops[1].color = bg_grad_color;
            dsc.grad.stops[1].frac = (uint8_t)bg_grad_stop;
            dsc.grad.stops[1].opa = opa;
        }

        dsc.p[0].x = points[0].x;
        dsc.p[0].y = points[0].y;
        dsc.p[1].x = points[1].x;
        dsc.p[1].y = points[1].y;
        dsc.p[2].x = points[2].x;
        dsc.p[2].y = points[2].y;
        drawTriangle(dsc);
    }

    void drawArc(const lv_draw_arc_dsc_t& dsc)
    {
        lv_draw_arc(&_layer, &dsc);
    }

    void drawArc(int32_t x,
                 int32_t y,
                 uint32_t radius,
                 int32_t start_angle,
                 int32_t end_angle,
                 lv_color_t color,
                 lv_opa_t opa = LV_OPA_COVER,
                 int32_t width = 1,
                 int32_t rounded = 0)
    {
        lv_draw_arc_dsc_t dsc;
        lv_draw_arc_dsc_init(&dsc);
        dsc.color = color;
        dsc.opa = opa;
        dsc.width = width;
        dsc.center.x = x;
        dsc.center.y = y;
        dsc.radius = radius;
        dsc.start_angle = start_angle;
        dsc.end_angle = end_angle;
        dsc.rounded = rounded;

        drawArc(dsc);
    }

    void drawLabel(const lv_draw_label_dsc_t& dsc, const lv_area_t& coords)
    {
        lv_draw_label(&_layer, &dsc, &coords);
    }

    void drawLabel(int32_t x,
                   int32_t y,
                   int32_t w,
                   int32_t h,
                   const char* text,
                   const lv_font_t* font,
                   lv_color_t color,
                   lv_opa_t opa = LV_OPA_COVER,
                   lv_text_align_t align = LV_TEXT_ALIGN_LEFT)
    {
        lv_draw_label_dsc_t dsc;
        lv_draw_label_dsc_init(&dsc);
        dsc.text = text;
        dsc.font = font;
        dsc.color = color;
        dsc.opa = opa;
        dsc.align = align;

        lv_area_t coords;
        coords.x1 = x;
        coords.y1 = y;
        coords.x2 = x + w - 1;
        coords.y2 = y + h - 1;

        drawLabel(dsc, coords);
    }

    void drawImage(const lv_draw_image_dsc_t& dsc, const lv_area_t& coords)
    {
        lv_draw_image(&_layer, &dsc, &coords);
    }

    void drawImage(int32_t x, int32_t y, const void* src, lv_opa_t opa = LV_OPA_COVER)
    {
        if (src == nullptr)
            return;

        lv_image_header_t header;
        if (lv_image_decoder_get_info(src, &header) != LV_RESULT_OK)
            return;

        lv_draw_image_dsc_t dsc;
        lv_draw_image_dsc_init(&dsc);
        dsc.src = src;
        dsc.opa = opa;

        lv_area_t coords;
        coords.x1 = x;
        coords.y1 = y;
        coords.x2 = x + header.w - 1;
        coords.y2 = y + header.h - 1;

        drawImage(dsc, coords);
    }

protected:
    std::vector<uint8_t> _buffer;
    lv_layer_t _layer;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit

#endif
