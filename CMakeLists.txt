cmake_minimum_required(VERSION 3.10)

project(sp)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-std=c++20 -Os)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)
