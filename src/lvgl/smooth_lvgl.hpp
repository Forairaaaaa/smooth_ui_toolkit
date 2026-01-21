/**
 * @file smooth_lvgl.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <lvgl.h>

#if LVGL_VERSION_MAJOR >= 9 && LVGL_VERSION_MINOR >= 3

#include "lvgl_cpp/obj.hpp"
#include "lvgl_cpp/label.hpp"
#include "lvgl_cpp/slider.hpp"
#include "lvgl_cpp/button.hpp"
#include "lvgl_cpp/switch.hpp"
#include "lvgl_cpp/line.hpp"
#include "lvgl_cpp/canvas.hpp"
#include "lvgl_cpp/chart.hpp"
#include "lvgl_cpp/image.hpp"
#include "lvgl_cpp/calendar.hpp"
#include "lvgl_cpp/roller.hpp"
#include "lvgl_cpp/spinner.hpp"
#include "lvgl_cpp/text_area.hpp"
#include "lvgl_cpp/table.hpp"
#include "lvgl_cpp/screen.hpp"
#include "lvgl_cpp/qrcode.hpp"
#include "lvgl_cpp/bar.hpp"
#include "number_flow/digit_flow.hpp"
#include "number_flow/number_flow.hpp"
#include "number_flow/number_flow_float.hpp"

#else
#error "Require LVGL version 9.3.0 or higher."
#endif
