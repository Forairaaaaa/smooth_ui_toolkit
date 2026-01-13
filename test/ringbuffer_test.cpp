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
#include <tools/ring_buffer/ring_buffer.hpp>

using namespace smooth_ui_toolkit;

void test_ring_buffer()
{
    std::cout << "Running enhanced tests on RingBuffer...\n";

    // 基础状态测试
    RingBuffer<int, 5> buffer;
    assert(buffer.empty());
    assert(buffer.size() == 0);
    assert(buffer.capacity() == 5);

    // 填充与 Full 状态测试
    for (int i = 1; i <= 5; ++i) {
        buffer.push(i);
    }
    assert(buffer.full());
    assert(buffer.size() == 5);
    assert(buffer.front() == 1);
    assert(buffer.back() == 5);

    // 覆盖写入测试 (Overwrite Enabled)
    buffer.setAllowOverwrite(true);
    buffer.push(6); // 此时应覆盖 1，r_index 指向 2
    assert(buffer.size() == 5);
    assert(buffer.front() == 2);
    assert(buffer.back() == 6);

    buffer.push(7); // 此时应覆盖 2，r_index 指向 3
    assert(buffer.front() == 3);
    assert(buffer.back() == 7);

    // peekAll 测试
    std::vector<int> expected_peek = {3, 4, 5, 6, 7};
    size_t peek_idx = 0;
    buffer.peekAll([&](const int& val, bool& stop) {
        assert(val == expected_peek[peek_idx++]);
    });
    assert(peek_idx == 5); // 确保遍历了所有元素

    // 禁止覆盖测试 (Overwrite Disabled)
    buffer.clear();
    buffer.setAllowOverwrite(false);
    for (int i = 1; i <= 5; ++i) {
        buffer.push(i);
    }
    buffer.push(99); // 应该被忽略
    assert(buffer.size() == 5);
    assert(buffer.back() == 5); // 依然是 5，不是 99

    // 循环读写测试 (Wrap-around)
    // 此时 buffer 满载 [1, 2, 3, 4, 5]
    buffer.pop(); // 剩 [_, 2, 3, 4, 5]
    buffer.pop(); // 剩 [_, _, 3, 4, 5]
    buffer.push(8);
    buffer.push(9); // 此时 buffer: [9, _, 3, 4, 5, 8] -> 逻辑上是 3,4,5,8,9
    assert(buffer.size() == 5);
    assert(buffer.front() == 3);
    assert(buffer.back() == 9);

    // popAll 验证
    std::vector<int> expected_pop = {3, 4, 5, 8, 9};
    size_t pop_idx = 0;
    buffer.popAll([&](int& val) {
        assert(val == expected_pop[pop_idx++]);
    });
    assert(buffer.empty());
    assert(pop_idx == 5);

    // Clear 测试
    buffer.push(100);
    buffer.clear();
    assert(buffer.empty());
    assert(buffer.size() == 0);

    std::cout << "All RingBuffer tests passed successfully!\n";
}

int main()
{
    test_ring_buffer();
    return 0;
}