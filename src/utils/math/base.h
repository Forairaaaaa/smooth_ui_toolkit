/**
 * @file base.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-15
 *
 * @copyright Copyright (c) 2025
 *
 */
// ref: https://github.com/godotengine/godot/blob/master/core/typedefs.h
#pragma once

namespace smooth_ui_toolkit {

template <typename T>
constexpr const T sign(const T m_v)
{
    return m_v > 0 ? +1.0f : (m_v < 0 ? -1.0f : 0.0f);
}

template <typename T, typename T2>
constexpr auto min(const T m_a, const T2 m_b)
{
    return m_a < m_b ? m_a : m_b;
}

template <typename T, typename T2>
constexpr auto max(const T m_a, const T2 m_b)
{
    return m_a > m_b ? m_a : m_b;
}

template <typename T, typename T2, typename T3>
constexpr auto clamp(const T m_a, const T2 m_min, const T3 m_max)
{
    return m_a < m_min ? m_min : (m_a > m_max ? m_max : m_a);
}

} // namespace smooth_ui_toolkit