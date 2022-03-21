cmake_minimum_required(VERSION 3.12)

add_executable(test-dingding test_dingding.cpp)
target_link_libraries(test-dingding cmocka dingding)
add_test(test-dingding ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test-dingding)
