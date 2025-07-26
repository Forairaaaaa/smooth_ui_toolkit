/**
 * @file animate.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators/generators.h"
#include "../generators/spring/spring.h"
#include "../generators/easing/easing.h"
#include <functional>
#include <memory>

namespace smooth_ui_toolkit {

namespace animate_repeat_type {
enum Type_t {
    loop = 0, // 循环播放
    reverse,  // 反向播放
};
}

namespace animate_state {
enum State_t {
    idle = 0,        // 空闲状态
    delaying,        // 等待开始（delay阶段）
    playing,         // 正在播放动画
    paused,          // 暂停
    repeat_delaying, // 重复等待阶段
    completed,       // 完成
    cancelled        // 取消
};
}

class Animate {
public:
    Animate() {}
    virtual ~Animate() {}

    // Disable copy constructor and copy assignment operator
    Animate(const Animate&) = delete;
    Animate& operator=(const Animate&) = delete;

    // Enable move constructor and move assignment operator
    Animate(Animate&& other) noexcept;
    Animate& operator=(Animate&& other) noexcept;

    // 参数参考：https://motion.dev/docs/animate#options

    // 开始值
    float start = 0.0f;
    // 结束值
    float end = 0.0f;
    // 动画开始前延迟（秒）
    float delay = 0.0f;
    // 重复次数，-1 表示无限循环
    int repeat = 0;
    // 重复类型
    animate_repeat_type::Type_t repeatType = animate_repeat_type::loop;
    // 重复间隔时间（秒）
    float repeatDelay = 0.0f;
    // 动画类型
    animation_type::Type_t animationType = animation_type::spring;
    // easing 动画配置，调用此方法，动画类型将自动切换为 easing
    EasingOptions_t& easingOptions();
    // spring 动画配置，调用此方法，动画类型将自动切换为 spring
    SpringOptions_t& springOptions();
    // 值更新回调
    void onUpdate(std::function<void(const float&)> callback)
    {
        _on_update = callback;
    }
    // 动画完成回调
    void onComplete(std::function<void()> callback)
    {
        _on_complete = callback;
    }

    /**
     * @brief Init animation
     *
     */
    void init();

    /**
     * @brief Start playing animation, If an animation is paused, it will resume from its current time, If animation has
     * finished, it will restart
     *
     */
    void play();

    /**
     * @brief Pauses the animation until resumed with play()
     *
     */
    void pause();

    /**
     * @brief Immediately completes the animation, running it to the end state
     *
     */
    void complete();

    /**
     * @brief Cancels the animation, reverting it to the initial state
     *
     */
    void cancel();

    /**
     * @brief Reset start and end value dynamically, spring animation will animate to new value with current velocity
     *
     * @param start
     * @param end
     */
    void retarget(const float& start, const float& end);

    /**
     * @brief Update animation, keep calling this method to update animation, callbacks will be invoked in this method
     *
     */
    void update();

    /**
     * @brief Update animation with explicit current time, more efficient for batch updates
     *
     * @param currentTime Current time in seconds
     */
    void update(const float& currentTime);

    /**
     * @brief Is key frame generator done
     *
     * @return true
     * @return false
     */
    inline bool done()
    {
        return get_key_frame_generator().done;
    }

    /**
     * @brief Get key frame generator current value
     *
     * @return float
     */
    inline float value()
    {
        return get_key_frame_generator().value;
    }

    inline animate_state::State_t currentPlayingState()
    {
        return _playing_state;
    }

protected:
    std::function<void(const float&)> _on_update;
    std::function<void()> _on_complete;
    std::unique_ptr<KeyFrameGenerator> _key_frame_generator;
    KeyFrameGenerator& get_key_frame_generator();
    animate_state::State_t _playing_state = animate_state::idle;
    float _start_time = 0.0f;
    float _pause_time = 0.0f;
    int _repeat_count = 0;
    bool _generator_dirty = true;

    void update_state_machine(const float& currentTime);
};

} // namespace smooth_ui_toolkit
