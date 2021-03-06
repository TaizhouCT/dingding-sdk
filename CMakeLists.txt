cmake_minimum_required(VERSION 3.12)
project(task-tzct)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(BUILD_DEBUG "Build with debug info." OFF)
if (BUILD_DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -g")
    message(STATUS "Build with -g for debug")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -O3")
    message(STATUS "Build with -O3 for release")
endif ()
add_definitions(-DSPDLOG_FMT_EXTERNAL=1)

option(BUILD_CLI "Build with cli" OFF)

include_directories(src)
add_subdirectory(src)

option(BUILD_TESTS "Build all tests." OFF)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
