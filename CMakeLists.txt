cmake_minimum_required(VERSION 3.8)
project(deeper_net)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/data_types/tensor.h include/data_types/array.h include/data_types/tools.h src/data_types/tensor_test.cc include/data_types/matrix.h src/data_types/matrix.cc src/data_types/matrix_test.cc include/misc/exception.h src/misc/exception.cc src/misc/exception_test.cc include/nn/operator.h src/nn/operator.cc)
add_executable(deeper_net ${SOURCE_FILES})

ADD_SUBDIRECTORY (gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(deeper_net gtest gtest_main)