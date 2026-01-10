/**
 * @file animate.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "../generators/generators.hpp"
#include "../generators/spring/spring.hpp"
#include "../generators/easing/easing.hpp"
#include <functional>
#include <memory>

namespace smooth_ui_toolkit {

enum class AnimateRepeatType {
    Loop = 0, // 循环播放
    Reverse,  // 反向播放
};

enum class AnimateState {
    Idle = 0,       // 空闲状态
    Delaying,       // 等待开始（delay阶段）
    Playing,        // 正在播放动画
    Paused,         // 暂停
    RepeatDelaying, // 重复等待阶段
    Completed,      // 完成
    Cancelled       // 取消
};

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
    AnimateRepeatType repeatType = AnimateRepeatType::Loop;
    // 重复间隔时间（秒）
    float repeatDelay = 0.0f;
    // 动画类型
    AnimationType animationType = AnimationType::Spring;
    // easing 动画配置，调用此方法，动画类型将自动切换为 easing
    EasingOptions_t& easingOptions();
    // spring 动画配置，调用此方法，动画类型将自动切换为 spring
    SpringOptions_t& springOptions();
    // 值更新回调
    void onUpdate(std::function<void(float)> callback)
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
    void retarget(float start, float end);

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
    void update(float currentTime);

    /**
     * @brief Update animation with delta time
     *
     * @param dt Delta time in seconds
     */
    void updateWithDelta(float dt);

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

    inline AnimateState currentPlayingState()
    {
        return _playing_state;
    }

protected:
    std::function<void(float)> _on_update;
    std::function<void()> _on_complete;
    std::unique_ptr<KeyFrameGenerator> _key_frame_generator;
    KeyFrameGenerator& get_key_frame_generator();
    AnimateState _playing_state = AnimateState::Idle;
    AnimateState _saved_state = AnimateState::Idle;
    float _last_tick = 0.0f;
    float _current_duration = 0.0f;
    int _repeat_count = 0;
    bool _generator_dirty = true;

    void update_state_machine(float dt);
};

} // namespace smooth_ui_toolkit
