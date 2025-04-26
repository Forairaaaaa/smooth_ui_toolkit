/**
 * @file ringbuffer_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <cassert>
#include <vector>
#include <utils/ring_buffer/ring_buffer.h>

using namespace smooth_ui_toolkit;

// 测试函数
void test_ring_buffer()
{
    std::cout << "Running tests on ring_buffer...\n";

    // 创建一个容量为5的ring buffer
    ring_buffer<int, 5> buffer;

    // 确保初始状态是空的
    assert(buffer.empty() && "Buffer should be empty initially");
    assert(buffer.size() == 0 && "Buffer size should be 0 initially");

    // Push元素到buffer
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);
    buffer.push(4);
    buffer.push(5);

    // Check size after pushing 5 elements
    assert(buffer.size() == 5 && "Buffer size should be 5 after pushing 5 elements");

    // Pop一个元素
    buffer.pop();
    assert(buffer.size() == 4 && "Buffer size should be 4 after popping 1 element");

    // Peek front and back
    assert(buffer.front() == 2 && "Front element should be 2");
    assert(buffer.back() == 5 && "Back element should be 5");

    // Push more elements to test overwriting when full
    buffer.push(6);
    assert(buffer.size() == 5 && "Buffer size should still be 5 after pushing 6");
    assert(buffer.front() == 2 && "Front element should be 2");

    buffer.push(7);
    assert(buffer.front() == 3 && "Front element should be 3 after overwrite");

    // Test popAll
    std::vector<int> result_map = {3, 4, 5, 6, 7};
    int index = 0;
    buffer.popAll([&result_map, &index](const int& value) {
        std::cout << "Popped value: " << value << "\n";
        assert((value == result_map[index]) && "Result is wrong");
        index++;
    });

    // Ensure buffer is empty after popping all elements
    assert(buffer.empty() && "Buffer should be empty after popping all elements");
    std::cout << "Test passed!\n";
}

int main()
{
    // 运行所有测试
    test_ring_buffer();
    return 0;
}