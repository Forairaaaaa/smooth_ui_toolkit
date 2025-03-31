/**
 * @file color.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "color.h"

namespace smooth_ui_toolkit {
namespace color {

Rgb_t hex_to_rgb(const uint32_t& hex)
{
    return Rgb_t((hex >> 16) & 0x0000FF, (hex >> 8) & 0x0000FF, hex & 0x0000FF);
}

Rgb_t hex_to_rgb(const std::string& hex)
{
    Rgb_t rgb;

    if (hex.size() != 7 || hex[0] != '#') {
        return rgb;
    }

    std::sscanf(hex.c_str(), "#%2hhx%2hhx%2hhx", &rgb.r, &rgb.g, &rgb.b);
    return rgb;
}

uint32_t rgb_to_hex(const Rgb_t& rgb)
{
    return ((rgb.r & 0xff) << 16) + ((rgb.g & 0xff) << 8) + (rgb.b & 0xff);
}

std::string rgb_to_hex_string(const Rgb_t& rgb)
{
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "#%02X%02X%02X", rgb.r, rgb.g, rgb.b);
    return std::string(buffer);
}

} // namespace color
} // namespace smooth_ui_toolkit