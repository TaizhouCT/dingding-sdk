cmake_minimum_required(VERSION 3.9)

file(GLOB INC dingding.h)
file(GLOB SRC *.cpp)

add_library(dingding SHARED ${SRC})
set_target_properties(dingding PROPERTIES PUBLIC_HEADER "${INC}")
set_target_properties(dingding PROPERTIES VERSION 1.0.0 SOVERSION 1)
target_link_libraries(dingding restclient-cpp fmt)
