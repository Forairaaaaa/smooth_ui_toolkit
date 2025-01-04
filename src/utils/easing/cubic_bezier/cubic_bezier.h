/**
 * @file cubic_bezier.h
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
// 参考：
// https://github.com/motiondivision/motion/blob/main/packages/framer-motion/src/easing/cubic-bezier.ts

namespace smooth_ui_toolkit {

std::function<float(float)> cubic_bezier(float mX1, float mY1, float mX2, float mY2);

}
