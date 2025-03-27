/**
 * @file obj.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-18
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://github.com/vpaeder/lvglpp
#pragma once
#include "lv_wrapper.h"
#include <lvgl.h>
#include <memory>

namespace smooth_ui_toolkit {
namespace lvgl_cpp {

/** \class Object
 *  \brief Wraps a lv_obj_t object. This is the generic LVGL object type.
 */
class Object : public PointerWrapper<lv_obj_t, lv_obj_del> {
public:
    ~Object()
    {
        // if lv_obj is invalid, this means it has already been deleted
        // by a LVGL function; it cannot be deleted again.
        if (!this->isValid()) {
            this->lv_obj.release();
        }
    }

    bool isValid() const
    {
        return lv_obj_is_valid(this->raw_ptr());
    }

    lv_obj_t* get()
    {
        return this->raw_ptr();
    }

    void setAlign(lv_align_t alignment)
    {
        lv_obj_set_align(this->raw_ptr(), alignment);
    }

    void setOpa(lv_opa_t opa, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_opa(this->raw_ptr(), opa, selector);
    }

    void setBgColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_bg_color(this->raw_ptr(), color, selector);
    }

    void setBgOpa(lv_opa_t opa, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_bg_opa(this->raw_ptr(), opa, selector);
    }

    void setPos(int32_t x, int32_t y)
    {
        lv_obj_set_pos(this->raw_ptr(), x, y);
    }

    void setX(int32_t x)
    {
        lv_obj_set_x(this->raw_ptr(), x);
    }

    void setY(int32_t y)
    {
        lv_obj_set_y(this->raw_ptr(), y);
    }

    void setSize(int32_t w, int32_t h)
    {
        lv_obj_set_size(this->raw_ptr(), w, h);
    }

    void setRadius(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_radius(this->raw_ptr(), value, selector);
    }

    void setBorderWidth(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_border_width(this->raw_ptr(), value, selector);
    }

    void setBorderColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_border_color(this->raw_ptr(), color, selector);
    }

    void setRotation(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_transform_rotation(this->raw_ptr(), value, selector);
    }

    void setTransformPivotX(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_transform_pivot_x(this->raw_ptr(), value, selector);
    }

    void setTransformPivotY(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_transform_pivot_y(this->raw_ptr(), value, selector);
    }

    void setTransformPivot(int32_t x, int32_t y, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_transform_pivot_x(this->raw_ptr(), x, selector);
        lv_obj_set_style_transform_pivot_y(this->raw_ptr(), y, selector);
    }

    void setScrollbarMode(lv_scrollbar_mode_t mode)
    {
        lv_obj_set_scrollbar_mode(this->raw_ptr(), mode);
    }

    void setPadding(int32_t top,
                    int32_t bottom,
                    int32_t left,
                    int32_t right,
                    lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_pad_top(this->raw_ptr(), top, selector);
        lv_obj_set_style_pad_bottom(this->raw_ptr(), bottom, selector);
        lv_obj_set_style_pad_left(this->raw_ptr(), left, selector);
        lv_obj_set_style_pad_right(this->raw_ptr(), right, selector);
    }

    void setOutlineWidth(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_outline_width(this->raw_ptr(), value, selector);
    }

    void setOutlineColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_outline_color(this->raw_ptr(), color, selector);
    }

    void moveBackground()
    {
        lv_obj_move_background(this->raw_ptr());
    }

    void moveForeground()
    {
        lv_obj_move_foreground(this->raw_ptr());
    }

    void hidden(bool hidden)
    {
        if (hidden) {
            addFlag(LV_OBJ_FLAG_HIDDEN);
        } else {
            removeFlag(LV_OBJ_FLAG_HIDDEN);
        }
    }

    void addFlag(lv_obj_flag_t flag)
    {
        lv_obj_add_flag(this->raw_ptr(), flag);
    }

    void removeFlag(lv_obj_flag_t flag)
    {
        lv_obj_remove_flag(this->raw_ptr(), flag);
    }

    int32_t getX()
    {
        lv_obj_update_layout(this->raw_ptr());
        return lv_obj_get_x(this->raw_ptr());
    }

    int32_t getX2()
    {
        lv_obj_update_layout(this->raw_ptr());
        return lv_obj_get_x2(this->raw_ptr());
    }

    int32_t getY()
    {
        lv_obj_update_layout(this->raw_ptr());
        return lv_obj_get_y(this->raw_ptr());
    }

    int32_t getY2()
    {
        lv_obj_update_layout(this->raw_ptr());
        return lv_obj_get_y2(this->raw_ptr());
    }

    int32_t getWidth()
    {
        lv_obj_update_layout(this->raw_ptr());
        return lv_obj_get_width(this->raw_ptr());
    }

    int32_t getHeight()
    {
        lv_obj_update_layout(this->raw_ptr());
        return lv_obj_get_height(this->raw_ptr());
    }

    void setTextColor(lv_color_t color, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_text_color(this->raw_ptr(), color, selector);
    }

    lv_color_t getTextColor(lv_style_selector_t selector = LV_PART_MAIN)
    {
        return lv_obj_get_style_text_color(this->raw_ptr(), selector);
    }

    void setTextFont(const lv_font_t* font, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_text_font(this->raw_ptr(), font, selector);
    }

    const lv_font_t* getTextFont(lv_style_selector_t selector = LV_PART_MAIN)
    {
        return lv_obj_get_style_text_font(this->raw_ptr(), selector);
    }

    void setFlexFlow(lv_flex_flow_t flow)
    {
        lv_obj_set_flex_flow(this->raw_ptr(), flow);
    }

    void setFlexAlign(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place)
    {
        lv_obj_set_flex_align(this->raw_ptr(), main_place, cross_place, track_cross_place);
    }

    void setPadRow(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_pad_row(this->raw_ptr(), value, selector);
    }

    void setPadColumn(int32_t value, lv_style_selector_t selector = LV_PART_MAIN)
    {
        lv_obj_set_style_pad_column(this->raw_ptr(), value, selector);
    }

    void addState(lv_state_t state)
    {
        lv_obj_add_state(this->raw_ptr(), state);
    }

    void removeState(lv_state_t state)
    {
        lv_obj_remove_state(this->raw_ptr(), state);
    }

    void addEventCb(lv_event_cb_t event_cb, lv_event_code_t filter, void* user_data = nullptr)
    {
        lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, user_data);
    }

    void onPressed(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        addEventCb(event_cb, LV_EVENT_PRESSED, user_data);
    }

    void onRelease(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        addEventCb(event_cb, LV_EVENT_RELEASED, user_data);
    }

    void onClick(lv_event_cb_t event_cb, void* user_data = nullptr)
    {
        addEventCb(event_cb, LV_EVENT_CLICKED, user_data);
    }
};

/** \brief Wraps a lv_obj_t object created with the given allocator.
 *  \tparam lv_allocator: an allocator function that returns a pointer
 *  to a lv_obj_t instance.
 */
template <auto lv_allocator>
class Widget : public Object {
protected:
    /** \fn void initialize()
     *  \brief Initialize object.
     */
    virtual void initialize()
    {
        this->lv_obj = LvPointerType(lv_allocator(nullptr));
    }

    virtual void initialize(lv_obj_t* parent)
    {
        this->lv_obj = LvPointerType(lv_allocator(parent));
    }

    /** \fn void initialize(Object & parent)
     *  \brief Initialize object and assign parent object.
     *  \param parent: parent LVGL object.
     */
    virtual void initialize(Object& parent)
    {
        this->lv_obj = LvPointerType(lv_allocator(parent.raw_ptr()));
    }

    /** \fn void initialize(const Object & parent)
     *  \brief Initialize object and assign parent object.
     *  \param parent: parent LVGL object.
     */
    virtual void initialize(const Object& parent)
    {
        this->lv_obj = LvPointerType(lv_allocator(const_cast<lv_cls_ptr>(parent.raw_ptr())));
    }

public:
    using Object::Object;

    /** \fn Widget()
     *  \brief Default constructor.
     */
    Widget()
    {
        this->initialize();
    }

    /** \fn Widget(lv_obj_t* parent)
     *  \brief Constructor with parent object.
     */
    Widget(lv_obj_t* parent)
    {
        this->initialize(parent);
    }

    /** \fn Widget(Object & parent)
     *  \brief Constructor with parent object.
     */
    Widget(Object& parent)
    {
        this->initialize(parent);
    }

    /** \fn Widget(const Object & parent)
     *  \brief Constructor with parent object.
     */
    Widget(const Object& parent)
    {
        this->initialize(parent);
    }

    /** \fn Widget(Widget & parent)
     *  \brief Constructor with parent widget object.
     *
     *  This is for cases when parent is of the same type.
     *  Compiler otherwise wants to use base class
     *  copy constructor, which doesn't exist.
     *  Note that we could define an explicit copy constructor
     *  in the Object class, but this leaves the default
     *  constructor out.
     *
     */
    Widget(Widget& parent)
    {
        this->initialize(parent);
    }

    /** \fn Widget(const Widget & parent)
     *  \brief Constructor with parent widget object.
     *
     *  This is for cases when parent is of the same type.
     *  Compiler otherwise wants to use base class
     *  copy constructor, which doesn't exist.
     *
     */
    Widget(const Widget& parent)
    {
        this->initialize(parent);
    }
};

/**
 * @brief Default lvgl object
 *
 */
class Container : public Widget<lv_obj_create> {
public:
    using Widget::Widget;
};

} // namespace lvgl_cpp
} // namespace smooth_ui_toolkit