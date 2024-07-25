/**
 * @file types.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "types.h"
#include "../math/math.h"

using namespace SmoothUIToolKit;

uint32_t Vector3D_t::toHex() { return Rgb2Hex(*this); }
