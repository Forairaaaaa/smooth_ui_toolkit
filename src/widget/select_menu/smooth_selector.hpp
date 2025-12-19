/**
 * @file smooth_selector.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-08-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "core/hal/hal.hpp"
#include "core/math/vector.hpp"
#include "animation/animate_vector/animate_vector2.hpp"
#include <cstdint>
#include <vector>

namespace smooth_ui_toolkit {

/**
 * @brief Menu base class with a smooth selector.
 * Selector move and reshape smoothly to match the option keyframes.
 * The option matched by the selector at that time, treated as the selected one.
 * Camera provides a smooth viewport position offset to keep selector inside the viewport.
 * Handy for list menu with a moving selector,
 * or moving options by simple postition and shape transition. (Use selector as coordinate origin)
 *
 * @note This is a base class, you should inherit it and override the virtual functions.
 */
class SmoothSelectorMenu {
public:
    virtual ~SmoothSelectorMenu() {}

    struct Option_t {
        Vector4 keyframe;
        void* userData = nullptr;
    };

    struct Config_t {
        // Selector move in loop
        bool moveInLoop = true;
        // Viewport size
        Vector2 cameraSize = {640, 480};
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

    // Configs
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

    // Options
    inline void addOption(Option_t optionProps)
    {
        _data.option_list.push_back(optionProps);
    }
    inline const std::vector<Option_t>& getOptionList()
    {
        return _data.option_list;
    }
    inline int getSelectedOptionIndex()
    {
        return _data.selected_option_index;
    }
    inline const Option_t& getSelectedOption()
    {
        return _data.option_list[_data.selected_option_index];
    }
    inline const Vector4& getSelectedKeyframe()
    {
        return getSelectedOption().keyframe;
    }

    // Selector
    inline AnimateVector2& getSelectorPostion()
    {
        return _data.selector_postion;
    }
    inline AnimateVector2& getSelectorShape()
    {
        return _data.selector_shape;
    }
    inline Vector4 getSelectorCurrentFrame()
    {
        return {getSelectorPostion().x, getSelectorPostion().y, getSelectorShape().x, getSelectorShape().y};
    }

    // Camera
    inline AnimateVector2& getCamera()
    {
        return _data.camera_offset;
    }
    inline Vector2 getCameraOffset()
    {
        return _data.camera_offset;
    }
    inline void setCameraSize(int width, int height)
    {
        _config.cameraSize.width = width;
        _config.cameraSize.height = height;
    }
    inline const Vector2& getCameraSize()
    {
        return _config.cameraSize;
    }

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
     * @brief Press selector to the passing key frame
     *
     * @param pressedKeyframe
     */
    virtual void press(const Vector4& pressedKeyframe);

    /**
     * @brief Is selector being pressed
     *
     * @return true
     * @return false
     */
    inline bool isPressing()
    {
        return _data.is_pressing;
    }

    /**
     * @brief Release selector
     *
     */
    virtual void release();

    /**
     * @brief Open selector to the passing key frame
     *
     * @param pressedKeyframe
     */
    virtual void open(const Vector4& pressedKeyframe);

    /**
     * @brief Is selector opening
     *
     * @return true
     * @return false
     */
    inline const bool& isOpening()
    {
        return _data.is_opening;
    }

    /**
     * @brief Close selector
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
        AnimateVector2 selector_postion;
        AnimateVector2 selector_shape;
        AnimateVector2 camera_offset;
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
    virtual void _update_selector_keyframe();
    virtual void _update_camera_keyframe();
};

} // namespace smooth_ui_toolkit