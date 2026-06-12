/**
 * @file observable_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2026-06-12
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <cassert>
#include <iostream>
#include <tools/observable/observable.hpp>
#include <tools/observable/single_observable.hpp>

using namespace smooth_ui_toolkit;

struct ObserverState_t {
    int call_count = 0;
    int value = 0;
};

static void on_int_changed(void* context, const int& newValue)
{
    auto* state = static_cast<ObserverState_t*>(context);
    state->call_count++;
    state->value = newValue;
}

void test_single_observable()
{
    SingleObservable<int> observable(1);
    ObserverState_t first;
    ObserverState_t second;

    observable.observe(&first, on_int_changed);
    assert(first.call_count == 1);
    assert(first.value == 1);

    observable.set(2);
    assert(first.call_count == 2);
    assert(first.value == 2);

    observable.observe(&second, on_int_changed);
    assert(second.call_count == 1);
    assert(second.value == 2);

    observable.set(3);
    assert(first.call_count == 2);
    assert(second.call_count == 2);
    assert(second.value == 3);

    observable.removeObserver();
    observable.set(4);
    assert(second.call_count == 2);
    assert(observable.get() == 4);
}

void test_observable()
{
    Observable<int> observable(10);
    ObserverState_t first;
    ObserverState_t second;

    size_t first_id = observable.observe(&first, on_int_changed);
    size_t second_id = observable.observe(&second, on_int_changed);
    assert(first_id != second_id);
    assert(first.call_count == 1);
    assert(second.call_count == 1);
    assert(first.value == 10);
    assert(second.value == 10);

    observable.set(11);
    assert(first.call_count == 2);
    assert(second.call_count == 2);
    assert(first.value == 11);
    assert(second.value == 11);

    observable.removeObserver(first_id);
    observable.set(12);
    assert(first.call_count == 2);
    assert(second.call_count == 3);
    assert(second.value == 12);

    observable.clearObservers();
    observable.set(13);
    assert(second.call_count == 3);
    assert(observable.get() == 13);
}

int main()
{
    std::cout << "Running Observable tests...\n";
    test_single_observable();
    test_observable();
    std::cout << "All Observable tests passed successfully!\n";
    return 0;
}
