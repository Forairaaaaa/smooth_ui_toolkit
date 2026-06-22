add_executable(ringbuffer_test ./ringbuffer_test.cpp)
target_link_libraries(ringbuffer_test ${PROJECT_NAME})

add_executable(observable_test ./observable_test.cpp)
target_link_libraries(observable_test ${PROJECT_NAME})

add_executable(area_system_test ./area_system_test.cpp)
target_link_libraries(area_system_test ${PROJECT_NAME})

add_executable(world_test ./world_test.cpp)
target_link_libraries(world_test ${PROJECT_NAME})
