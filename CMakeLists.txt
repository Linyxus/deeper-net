cmake_minimum_required(VERSION 3.8)
project(deeper_net)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp src/data_types/tensor.h src/data_types/array.h)
add_executable(deeper_net ${SOURCE_FILES})