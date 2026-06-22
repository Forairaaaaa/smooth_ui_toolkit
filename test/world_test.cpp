#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <games/core/core.h>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::games;

struct LifecycleCounters {
    int ready = 0;
    int update = 0;
    int destroy = 0;
};

class LifecycleObject : public GameObject {
public:
    explicit LifecycleObject(LifecycleCounters& counters) : _counters(counters) {}

    void onReady() override
    {
        _counters.ready++;
    }

    void onUpdate(float dt) override
    {
        (void)dt;
        _counters.update++;
    }

    void onDestroy() override
    {
        _counters.destroy++;
    }

private:
    LifecycleCounters& _counters;
};

class AreaLifecycleObject : public LifecycleObject {
public:
    AreaLifecycleObject(LifecycleCounters& counters, Vector2 position, Vector2 size) : LifecycleObject(counters)
    {
        add(std::make_unique<Transform>(position));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>());
    }
};

class OrderedAreaLifecycleObject : public GameObject {
public:
    OrderedAreaLifecycleObject(LifecycleCounters& counters, std::vector<int>& events, Vector2 position, Vector2 size)
        : _counters(counters), _events(events)
    {
        add(std::make_unique<Transform>(position));
        add(std::make_unique<RectShape>(size));
        add(std::make_unique<Area>());
    }

    void onDestroy() override
    {
        _counters.destroy++;
        _events.push_back(2);
    }

private:
    LifecycleCounters& _counters;
    std::vector<int>& _events;
};

void test_destroy_requested_pending_object_skips_ready_and_update()
{
    World world;
    LifecycleCounters counters;

    auto* object = world.createObject(std::make_unique<LifecycleObject>(counters));
    object->requestDestroy();

    world.update(1.0f / 60.0f);

    assert(counters.ready == 0);
    assert(counters.update == 0);
    assert(counters.destroy == 1);
}

void test_area_exit_is_emitted_before_destroy()
{
    World world;
    LifecycleCounters first_counters;
    LifecycleCounters second_counters;
    std::vector<int> events;

    auto* first = world.createObject(std::make_unique<OrderedAreaLifecycleObject>(
        first_counters, events, Vector2{0.0f, 0.0f}, Vector2{20.0f, 20.0f}));
    auto* second = world.createObject(
        std::make_unique<AreaLifecycleObject>(second_counters, Vector2{5.0f, 0.0f}, Vector2{20.0f, 20.0f}));

    auto* first_area = first->get<Area>();
    auto* second_area = second->get<Area>();

    first_area->onExited.connect([&](GameObject&) {
        events.push_back(1);
    });
    second_area->onExited.connect([&](GameObject&) {
        events.push_back(1);
    });

    world.update(1.0f / 60.0f);
    assert(first_area->overlaps.count(second) == 1);
    assert(second_area->overlaps.count(first) == 1);

    first->requestDestroy();
    first_counters.destroy = 0;

    world.update(1.0f / 60.0f);

    assert(first_counters.destroy == 1);
    assert(events.size() >= 2);
    assert(events.front() == 1);
    assert(events.back() == 2);
}

int main()
{
    std::cout << "Running World tests...\n";
    test_destroy_requested_pending_object_skips_ready_and_update();
    test_area_exit_is_emitted_before_destroy();
    std::cout << "All World tests passed successfully!\n";
    return 0;
}
