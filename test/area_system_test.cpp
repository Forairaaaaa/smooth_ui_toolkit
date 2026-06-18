#include <cassert>
#include <iostream>
#include <memory>
#include <games/core/core.h>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::games;

class AreaTestObject : public GameObject {
public:
    AreaTestObject(Vector2 position, Vector2 size)
    {
        add(std::make_unique<Transform>(position));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>());
    }
};

void test_destroyed_area_removes_reverse_overlap()
{
    World world;

    auto* first = world.createObject(std::make_unique<AreaTestObject>(Vector2{0.0f, 0.0f}, Vector2{20.0f, 20.0f}));
    auto* second = world.createObject(std::make_unique<AreaTestObject>(Vector2{5.0f, 0.0f}, Vector2{20.0f, 20.0f}));

    auto* first_area = first->get<Area>();
    auto* second_area = second->get<Area>();

    int first_entered = 0;
    int first_exited = 0;
    int second_entered = 0;
    int second_exited = 0;

    first_area->onEntered.connect([&](GameObject&) {
        first_entered++;
    });
    first_area->onExited.connect([&](GameObject&) {
        first_exited++;
    });
    second_area->onEntered.connect([&](GameObject&) {
        second_entered++;
    });
    second_area->onExited.connect([&](GameObject&) {
        second_exited++;
    });

    world.update(1.0f / 60.0f);

    assert(first_entered == 1);
    assert(second_entered == 1);
    assert(first_area->overlaps.count(second) == 1);
    assert(second_area->overlaps.count(first) == 1);

    first->requestDestroy();
    world.update(1.0f / 60.0f);

    assert(first_exited == 1);
    assert(second_exited == 1);
    assert(second_area->overlaps.empty());
}

int main()
{
    std::cout << "Running AreaSystem tests...\n";
    test_destroyed_area_removes_reverse_overlap();
    std::cout << "All AreaSystem tests passed successfully!\n";
    return 0;
}
