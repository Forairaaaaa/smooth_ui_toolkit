/**
 * @file ease.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <functional>

namespace smooth_ui_toolkit {

extern std::function<float(float)> ease_in;
extern std::function<float(float)> ease_out;
extern std::function<float(float)> ease_in_out;

} // namespace smooth_ui_toolkit
