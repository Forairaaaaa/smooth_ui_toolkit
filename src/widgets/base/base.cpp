/**
 * @file base.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "base.h"

using namespace SmoothUIToolKit::Widgets;

WidgetBase::~WidgetBase()
{
    for (const auto& i : _data.children)
    {
        delete i;
    }
}

void WidgetBase::setParent(WidgetBase* parent) { parent->addChild(this); }

bool WidgetBase::isChild(WidgetBase* child)
{
    if (child == nullptr || child == this)
        return false;

    for (const auto& i : _data.children)
    {
        if (i == child)
            return true;
        if (i->isChild(child))
            return true;
    }
    return false;
}

void WidgetBase::addChild(WidgetBase* child)
{
    if (isChild(child))
        return;
    _data.children.push_back(child);
    child->setParent(this);
}

void WidgetBase::setEnable(bool isEnable)
{
    _data.isEnable = isEnable;
    for (const auto i : _data.children)
        i->setEnable(isEnable);
}

void WidgetBase::setVisible(bool isVisible)
{
    _data.isVisible = isVisible;
    for (const auto i : _data.children)
        i->setVisible(isVisible);
}

void WidgetBase::update(const TimeSize_t& currentTime)
{
    // Update
    if (!_data.isEnable)
        return;
    onUpdate(currentTime);

    // Render
    if (_data.isVisible)
        onRender();

    // Children
    updateChildren(currentTime);
}

void WidgetBase::updateChildren(const std::uint32_t& currentTime)
{
    for (const auto i : _data.children)
        i->update(currentTime);
}
