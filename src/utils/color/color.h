/**
 * @file color.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <cstdint>
#include <string>

namespace smooth_ui_toolkit {
namespace color {

class Rgb_t;

/**
 * @brief Convert a hex color to a rgb color, e.g. 0xffffff -> rgb(255, 255, 255)
 *
 * @param hex
 * @return Rgb_t
 */
Rgb_t hex_to_rgb(const uint32_t& hex);

/**
 * @brief Convert a hex color to a rgb color, e.g. #ffffff -> rgb(255, 255, 255)
 *
 * @param hex
 * @return Rgb_t
 */
Rgb_t hex_to_rgb(const std::string& hex);

/**
 * @brief Convert a rgb color to a hex color, e.g. rgb(255, 255, 255) -> 0xffffff
 *
 * @param rgb
 * @return uint32_t
 */
uint32_t rgb_to_hex(const Rgb_t& rgb);

/**
 * @brief Convert a rgb color to a hex color, e.g. rgb(255, 255, 255) -> #ffffff
 *
 * @param rgb
 * @return std::string
 */
std::string rgb_to_hex_string(const Rgb_t& rgb);

/**
 * @brief RGB888 color
 *
 */
struct Rgb_t {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    Rgb_t() {}
    Rgb_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    Rgb_t(uint32_t hex)
    {
        *this = hex_to_rgb(hex);
    }
    Rgb_t(const std::string& hex)
    {
        *this = hex_to_rgb(hex);
    }

    Rgb_t& operator=(uint32_t hex)
    {
        *this = hex_to_rgb(hex);
        return *this;
    }

    Rgb_t& operator=(const std::string& hex)
    {
        *this = hex_to_rgb(hex);
        return *this;
    }

    inline uint32_t toHex() const
    {
        return rgb_to_hex(*this);
    }

    inline std::string toHexString() const
    {
        return rgb_to_hex_string(*this);
    }
};

} // namespace color
} // namespace smooth_ui_toolkit