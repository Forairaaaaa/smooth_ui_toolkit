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
#include "../../animation/animate_value/animate_value.h"
#include "utils/easing/ease.h"
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
 * @brief 差值混合
 *
 * @param bg
 * @param fg
 * @return Rgb_t
 */
Rgb_t blend_in_difference(Rgb_t bg, Rgb_t fg);

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

struct AnimateRgb_t : public Rgb_t {
    using Rgb_t::Rgb_t;

    float duration = 1.0f;

    AnimateValue r_anim;
    AnimateValue g_anim;
    AnimateValue b_anim;

    inline void begin()
    {
        r_anim.easingOptions().easingFunction = ease::linear;
        g_anim.easingOptions().easingFunction = ease::linear;
        b_anim.easingOptions().easingFunction = ease::linear;
        r_anim.easingOptions().duration = duration;
        g_anim.easingOptions().duration = duration;
        b_anim.easingOptions().duration = duration;
        teleport(r, g, b);
    }

    inline void update()
    {
        r = r_anim;
        g = g_anim;
        b = b_anim;
    }

    inline void teleport(uint8_t r, uint8_t g, uint8_t b)
    {
        r_anim.teleport(r);
        g_anim.teleport(g);
        b_anim.teleport(b);
    }
    inline void teleport(const Rgb_t& rgb)
    {
        teleport(rgb.r, rgb.g, rgb.b);
    }
    inline void teleport(uint32_t hex)
    {
        teleport(hex_to_rgb(hex));
    }
    inline void teleport(const std::string& hex)
    {
        teleport(hex_to_rgb(hex));
    }

    inline void move(uint8_t r, uint8_t g, uint8_t b)
    {
        r_anim.move(r);
        g_anim.move(g);
        b_anim.move(b);
    }
    inline void move(const Rgb_t& rgb)
    {
        move(rgb.r, rgb.g, rgb.b);
    }
    inline void move(uint32_t hex)
    {
        move(hex_to_rgb(hex));
    }
    inline void move(const std::string& hex)
    {
        move(hex_to_rgb(hex));
    }

    AnimateRgb_t& operator=(const Rgb_t& rgb)
    {
        move(rgb);
        return *this;
    }
    AnimateRgb_t& operator=(uint32_t hex)
    {
        move(hex);
        return *this;
    }
    AnimateRgb_t& operator=(const std::string& hex)
    {
        move(hex);
        return *this;
    }

    inline Rgb_t target()
    {
        return Rgb_t(r_anim.end, g_anim.end, b_anim.end);
    }

    inline bool done()
    {
        return r_anim.done() && g_anim.done() && b_anim.done();
    }
};

} // namespace color
} // namespace smooth_ui_toolkit