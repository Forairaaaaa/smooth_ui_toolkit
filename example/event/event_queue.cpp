/**
 * @file event_queue.cpp
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
#include <smooth_ui_toolkit.h>

using namespace smooth_ui_toolkit;

int main()
{
    EventQueue<int> event_queue;

    std::thread producer([&]() {
        for (int i = 1; i < 6; i++) {
            event_queue.emit(i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread consumer([&]() {
        bool is_running = true;
        while (is_running) {
            event_queue.poll([&](int event) {
                std::cout << "on event: " << event << std::endl;
                if (event == 5) {
                    is_running = false;
                }
            });
        }
    });

    producer.join();
    consumer.join();
    return 0;
}