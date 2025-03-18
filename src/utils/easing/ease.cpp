/**
 * @file ease.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "ease.h"
#include "cubic_bezier/cubic_bezier.h"

std::function<float(float)> smooth_ui_toolkit::ease_in = smooth_ui_toolkit::cubic_bezier(0.42, 0, 1, 1);
std::function<float(float)> smooth_ui_toolkit::ease_out = smooth_ui_toolkit::cubic_bezier(0, 0, 0.58, 1);
std::function<float(float)> smooth_ui_toolkit::ease_in_out = smooth_ui_toolkit::cubic_bezier(0.42, 0, 0.58, 1);
