cmake_minimum_required(VERSION 3.8)
project(deeper_net)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/data_types/tensor.h include/data_types/array.h include/data_types/tools.h)
add_executable(deeper_net ${SOURCE_FILES})

ADD_SUBDIRECTORY (gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(deeper_net gtest gtest_main)