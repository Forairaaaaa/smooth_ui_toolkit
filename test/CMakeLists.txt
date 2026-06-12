add_executable(ringbuffer_test ./ringbuffer_test.cpp)
target_link_libraries(ringbuffer_test ${PROJECT_NAME})

add_executable(observable_test ./observable_test.cpp)
target_link_libraries(observable_test ${PROJECT_NAME})
