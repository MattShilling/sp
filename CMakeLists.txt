cmake_minimum_required(VERSION 3.10)

project(sp)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-std=c++2a -Os)

include(CTest)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party/Simple-FFT/include/simple_fft)
include_directories(${CMAKE_SOURCE_DIR}/third_party/AudioFile/include)

add_subdirectory(src)
