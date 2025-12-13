/**
 * @file signal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <smooth_ui_toolkit.hpp>

using namespace smooth_ui_toolkit;

void consumer(int id, Signal<std::string, int>& signal)
{
    bool is_running = true;
    signal.connect([&](std::string str, int num) {
        std::cout << "[" << id << "] on signal: " << str << " " << num << std::endl;
        if (str == "done") {
            is_running = false;
        }
    });
    while (is_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    Signal<std::string, int> signal;

    std::thread consumer_1([&]() {
        consumer(1, signal);
    });
    std::thread consumer_2([&]() {
        consumer(2, signal);
    });

    std::thread producer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for (int i = 1; i < 6; i++) {
            signal.emit("hello", i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        signal.emit("done", 114514);
    });

    producer.join();
    consumer_1.join();
    consumer_2.join();
    return 0;
}