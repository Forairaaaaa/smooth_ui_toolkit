/**
 * @file ease.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://easings.net
#pragma once

namespace smooth_ui_toolkit {
namespace ease {

float linear(float t);
float ease_in_sine(float t);
float ease_out_sine(float t);
float ease_in_out_sine(float t);

float ease_in_quad(float t);
float ease_out_quad(float t);
float ease_in_out_quad(float t);

float ease_in_cubic(float t);
float ease_out_cubic(float t);
float ease_in_out_cubic(float t);

float ease_in_quart(float t);
float ease_out_quart(float t);
float ease_in_out_quart(float t);

float ease_in_quint(float t);
float ease_out_quint(float t);
float ease_in_out_quint(float t);

float ease_in_expo(float t);
float ease_out_expo(float t);
float ease_in_out_expo(float t);

float ease_in_circ(float t);
float ease_out_circ(float t);
float ease_in_out_circ(float t);

float ease_in_back(float t);
float ease_out_back(float t);
float ease_in_out_back(float t);

float ease_in_elastic(float t);
float ease_out_elastic(float t);
float ease_in_out_elastic(float t);

float ease_out_bounce(float t);
float ease_in_bounce(float t);
float ease_in_out_bounce(float t);

} // namespace ease
} // namespace smooth_ui_toolkit
