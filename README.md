# Smooth UI Toolkit

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/SmoothMenuDemo2.gif?raw=true)

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/SmoothMenuDemo1.gif?raw=true)

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/Mix1.gif?raw=true)

带动画曲线插值的 UI 抽象工具集，无依赖

- 动画曲线插值抽象，定点数优化浮点计算，自定义曲线
- 选择菜单抽象，适用于普通选择菜单、启动器等
- 更多控件抽象 (TODO)

视频：https://www.bilibili.com/video/BV1TT4y1W7tz

模拟器：https://github.com/Forairaaaaa/smooth_ui_toolkit_simu

## 文件树

```shell
.
├── core
│   ├── easing_path                   // 动画曲线
│   ├── smooth_drag
│   ├── transition                    // 一维过渡抽象
│   ├── transition2d                  // 二维过渡抽象
│   └── types                         // 类型定义
├── select_menu                       // 选择菜单抽象
│   ├── base
│   ├── smooth_options
│   └── smooth_selector
├── smooth_widget                     // TODO
│   ├── base
│   └── button
└── utils
    └── fpm                           // 定点数
```

## Core

### EasingPath

动画曲线函数，参考：https://easings.net/,  [示例](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/simu_project/smooth_ui_toolkit_test/easing_path/easing_path_test.cpp#L30)：

```cpp
using namespace SmoothUIToolKit;

// 避免浮点运算，映射到 0 ~ EasingPath::maxT
for (int t = 0; t < EasingPath::maxT; t++)
{
    auto x = EasingPath::easeInQuad(t);
    // auto x = EasingPath::easeOutQuad(t);
    // auto x = EasingPath::easeInOutQuad(t);
    // auto x = EasingPath::easeInCubic(t);
    // ...

    spdlog::info("x({}) = {}", t, x);
}
```

更多具体内容在[头文件定义](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/src/core/easing_path/easing_path.h)

### Transition

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/EasingPath.gif?raw=true)

一维过渡抽象，[示例](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/dd72391ed4b9aed22d91b95fc760bb65d9fe5807/simu_project/smooth_ui_toolkit_test/transition/transition_test.cpp#L24)：

```cpp
using namespace SmoothUIToolKit;

Transition t;

// 初始值
t.setStartValue(0);
// 结束值
t.setEndValue(100);
// 过渡时间
t.setDuration(400);
// 过渡曲线
t.setTransitionPath(EasingPath::easeOutBack);

// Update 回调函数
t.setUpdateCallback([](Transition* transition) {
    spdlog::info("value: {}", transition->getValue());
});

// 开始过渡, 传入当前时间 (ms)
t.start(HAL::Millis());

while (1)
{
    // 更新过渡，传入当前时间 (ms)
    t.update(HAL::Millis());
    // update方法会在最后调用回调函数，当然也可以在外部直接拿值
    t.getValue();
}
```

更多具体内容在[头文件定义](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/src/core/transition/transition.h)

### Transition2D

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/Transition2D.gif?raw=true)

二维过渡抽象，最常用的一集 (xy 坐标，wh 形状...)，[示例](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/dd72391ed4b9aed22d91b95fc760bb65d9fe5807/simu_project/smooth_ui_toolkit_test/transition_2d/transition_2d_test.cpp#L25)：

```cpp
using namespace SmoothUIToolKit;

Transition2D t2d;

// 配置方法和一维无异，略
...
// 区别是可以单独配置他们的过渡参数
t2d.getXTransition()...
t2d.getYTransition()...

// 一样可以注册回调
t2d.setUpdateCallback([](Transition2D* transition2d) {
    spdlog::info("i'm at ({}, {})", transition2d->getValue().x, transition2d->getValue().y);
});

// 跳到指定坐标, 没有过渡, 默认构造函数会跳到(0,0)
t2d.jumpTo(100, 233);

// 移动到指定坐标，有过渡
t2d.moveTo(666, 777);

while (1)
{
    // 更新过渡，传入当前时间 (ms)
    t2d.update(HAL::Millis());
}
```

更多具体内容在[头文件定义](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/src/core/transition2d/transition2d.h)

## SelectMenu

选择菜单的抽象，可以用于实现：

- 带有一个飞来飞去的选择指示器的选择菜单
- 滚轮选择菜单
- 选项会变形的环形菜单等

### SmoothSelector

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/SmoothSelector.gif?raw=true)

三个概念：

- **选项关键帧列表**，存着每一个选项的关键帧  `x, y, w, h`
- **选择器**，根据输入，移动到选项关键帧的 `x, y`，变形到选项关键帧的 `w, h`
- **摄像机**，自动移动到合适的 `x, y`，以保持选择器在摄像机 `w, h` 中

因此只有**选择器**和**摄像机**有运动过渡，选项可视为静态不动的

[示例](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/dd72391ed4b9aed22d91b95fc760bb65d9fe5807/simu_project/smooth_widget_test/select_menu_selector.cpp#L113)：

```cpp
using namespace SmoothUIToolKit;
using namespace SmoothUIToolKit::SelectMenu;

class SmoothSelector_test : public SmoothSelector
{
    // 重写读取输入回调
    void onReadInput() override
    {
        // 按键Up clicked
        if (...)
            goLast();
        
        // 按键Down clicked
        else if (...)
            goNext();
    }
	
    // 重写渲染回调
    void onRender() override
    {
        // 清屏
        ...

        // 渲染选项
        for (auto& i : getOptionList())
        {
            ...(i.keyframe.x,
                i.keyframe.y,
                i.keyframe.w,
                i.keyframe.h);
        }

        // 渲染选择器
        auto cf = getSelectorCurrentFrame();
        ...(cf.x,
            cf.y,
            cf.w,
            cf.h);

        // 推屏
        ...
    }
};

SmoothSelector_test menu;

// 添加选项
menu.addOption({{0, 0, 100, 20}, nullptr});
menu.addOption({{0, 20, 100, 20}, nullptr});
menu.addOption({{0, 40, 100, 20}, nullptr});

while (1)
{
    // 更新菜单，传入当前时间 (ms)
    menu.update(HAL::Millis());
}
```

更多具体内容在[头文件定义](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/src/select_menu/smooth_selector/smooth_selector.h)

### SmoothOptions

![](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/main/pics/SmoothOptions.gif?raw=true)

两个概念：

- **选项**，根据输入，移动到关键帧的 `x, y`，变形到选项关键帧的 `w, h`

- **关键帧列表**，存着与选项数量相同的关键帧  `x, y, w, h`

因此每个**选项**都有运动过渡，对应数量的关键帧可视为静态不动的。选项们连续地、循环地绕着关键帧列表移动、变形。

[示例](https://github.com/Forairaaaaa/smooth_ui_toolkit_simu/blob/dd72391ed4b9aed22d91b95fc760bb65d9fe5807/simu_project/smooth_widget_test/select_menu_option.cpp#L99)：

```cpp
using namespace SmoothUIToolKit;
using namespace SmoothUIToolKit::SelectMenu;

class SmoothOption_Test : public SmoothOptions
{
    // 重写读取输入回调
    void onReadInput() override
    {
        // 按键Up clicked
        if (...)
            goLast();
        
        // 按键Down clicked
        else if (...)
            goNext();
    }
	
    // 重写渲染回调
    void onRender() override
    {
        // 清屏
        ...

        // 渲染选项
        for (int i = 0; i < getOptionList().size(); i++)
        {
            auto ocf = getOptionCurrentFrame(i);
			...(ocf.x, 
                ocf.y, 
                ocf.w, 
                ocf.h);
        }

        // 推屏
        ...
    }
};

SmoothOption_Test menu;

// 添加选项
for (int i = 0; i < 5; i++)
{
    menu.addOption();
    menu.setLastKeyframe({10 * i, 20 * i, 100, 20});
}

while (1)
{
    // 更新菜单，传入当前时间 (ms)
    menu.update(HAL::Millis());
}
```

更多具体内容在[头文件定义](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/src/select_menu/smooth_options/smooth_options.h)

