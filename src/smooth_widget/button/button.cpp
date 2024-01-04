/**
 * @file button.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "button.h"


using namespace SmoothUIToolKit::SmoothWidget;


void Button::update(std::uint32_t currentTime)
{
    _onUpdate();
}


void Button::hover(int x, int y)
{
    _onHover();
}


void Button::drag(int x, int y)
{
    _onDrag();
}


void Button::drop()
{
    _onDrop();
}

