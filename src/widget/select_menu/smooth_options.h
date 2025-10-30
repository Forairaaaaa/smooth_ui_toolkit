/**
 * @file smooth_options.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-10-30
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "utils/hal/hal.h"
#include "utils/math/vector.h"
#include "animation/animate_vector/animate_vector2.h"
#include <cstdint>
#include <vector>

namespace smooth_ui_toolkit {

/**
 * @brief Menu with smooth options.
 * Option moves in loop to match the keyframe list, keyframe num equals option num.
 * The option matching the first keyframe at that time, treated as the selected one.
 * Each options has their own transition,
 * handy for loop menu with complex position and shape transition.
 *
 * @note This is a base class, you should inherit it and override the virtual functions.
 */
class SmoothOptionsMenu {
public:
    virtual ~SmoothOptionsMenu() {}

    struct Option_t {
        AnimateVector2 position;
        AnimateVector2 shape;
        void* userData = nullptr;
    };

    struct Config_t {
        // Interval of onReadInput() callback
        uint32_t readInputInterval = 20;
        // Interval of onRender() callback
        uint32_t renderInterval = 15;
    };

    virtual void onGoLast() {}
    virtual void onGoNext() {}
    virtual void onPress() {}
    virtual void onRelease() {}
    virtual void onClick() {}
    virtual void onOpenEnd() {}
    virtual void onUpdate(const uint32_t& currentTime) {}
    virtual void onReadInput() {}
    virtual void onRender() {}

    // Config
    inline const Config_t& getConfig()
    {
        return _config;
    }
    inline void setConfig(Config_t cfg)
    {
        _config = cfg;
    }
    inline Config_t& setConfig()
    {
        return _config;
    }

    // Keyframe
    inline const std::vector<Vector4>& getKeyframeList()
    {
        return _data.keyframe_list;
    }
    inline const Vector4& getKeyframe(const int& index)
    {
        return _data.keyframe_list[index];
    }
    inline void setKeyframe(int index, Vector4 keyframe)
    {
        _data.keyframe_list[index] = keyframe;
    }
    inline Vector4& setKeyframe(int index)
    {
        return _data.keyframe_list[index];
    }
    inline void setLastKeyframe(Vector4 keyframe)
    {
        _data.keyframe_list.back() = keyframe;
    }

    // Options
    void addOption(void* userData = nullptr);
    inline Option_t& setOption(int index)
    {
        return _data.option_list[index];
    }
    inline const std::vector<Option_t>& getOptionList()
    {
        return _data.option_list;
    }
    inline std::vector<Option_t>& setOptionList()
    {
        return _data.option_list;
    }
    inline Option_t& getOption(const int& index)
    {
        return _data.option_list[index];
    }
    inline Option_t& getSelectedOption()
    {
        return _data.option_list[getMatchingOptionIndex(0)];
    }
    inline int getSelectedOptionIndex()
    {
        return getMatchingOptionIndex(0);
    }
    inline Vector4 getOptionCurrentFrame(const int& index)
    {
        return {getOption(index).position.x,
                getOption(index).position.y,
                getOption(index).shape.x,
                getOption(index).shape.y};
    }

    /**
     * @brief Get the option index that the keyframe is currently matching
     * This can be used to render props in keyframe order
     *
     * @param keyframeIndex
     * @return int matched option index
     */
    int getMatchingOptionIndex(const int& keyframeIndex);

    /**
     * @brief Select last one
     *
     */
    virtual void goLast();

    /**
     * @brief Select next one
     *
     */
    virtual void goNext();

    /**
     * @brief Move to option smoothly
     *
     * @param optionIndex
     */
    virtual void moveTo(int optionIndex);

    /**
     * @brief Jump to the option with on transition
     *
     * @param optionIndex
     */
    virtual void jumpTo(int optionIndex);

    /**
     * @brief Press the selected option to the passing key frame
     *
     * @param pressedKeyframe
     */
    virtual void press(const Vector4& pressedKeyframe);

    /**
     * @brief Is the selected option being pressed
     *
     * @return true
     * @return false
     */
    inline bool isPressing()
    {
        return _data.is_pressing;
    }

    /**
     * @brief Release the selected option
     *
     */
    virtual void release();

    /**
     * @brief Open the selected option to the passing key frame
     *
     * @param pressedKeyframe
     */
    virtual void open(const Vector4& pressedKeyframe);

    /**
     * @brief Is the selected option opening
     *
     * @return true
     * @return false
     */
    inline const bool& isOpening()
    {
        return _data.is_opening;
    }

    /**
     * @brief Close the selected option
     *
     */
    virtual void close();

    /**
     * @brief Update menu
     *
     * @param currentTime
     */
    inline void update()
    {
        update(ui_hal::get_tick());
    }
    virtual void update(const uint32_t& currentTime);

protected:
    struct Data_t {
        std::vector<Option_t> option_list;
        std::vector<Vector4> keyframe_list;
        int selected_option_index = 0;
        uint32_t read_input_time_count = 0;
        uint32_t render_time_count = 0;
        bool is_changed = true;
        bool is_pressing = false;
        bool was_released = false;
        bool is_opening = false;
        bool was_opened = false;
    };
    Data_t _data;
    Config_t _config;
    virtual void _update_option_keyframe(bool isJump = false);
    virtual void _invoke_option_update(const uint32_t& currentTime);
};

} // namespace smooth_ui_toolkit
