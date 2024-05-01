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
    for (const auto& i : _base_data.children)
    {
        delete i;
    }
}

void WidgetBase::setParent(WidgetBase* parent) { parent->addChild(this); }

bool WidgetBase::isChild(WidgetBase* child)
{
    if (child == nullptr || child == this)
        return false;

    for (const auto& i : _base_data.children)
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
    _base_data.children.push_back(child);
    child->setParent(this);
}

void WidgetBase::iterateChildren(std::function<void(WidgetBase* child)> callback)
{
    for (const auto i : _base_data.children)
        callback(i);
}

void WidgetBase::update(const TimeSize_t& currentTime)
{
    // Update
    if (!_base_data.isEnable)
        return;
    onUpdate(currentTime);

    // Children
    iterateChildren([&](WidgetBase* child) { child->update(currentTime); });

    // Render
    if (isRoot() && _base_data.renderOnUpdate)
        render();
}

void WidgetBase::render()
{
    if (!_base_data.isVisible)
        return;

    onRender();
    iterateChildren([&](WidgetBase* child) { child->render(); });
    onPostRender();
}

void WidgetBase::init()
{
    onInit();
    iterateChildren([&](WidgetBase* child) { child->init(); });
}

void WidgetBase::reset()
{
    onReset();
    iterateChildren([&](WidgetBase* child) { child->reset(); });
}
