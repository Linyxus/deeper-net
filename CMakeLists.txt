cmake_minimum_required(VERSION 3.8)
project(deeper_net)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp include/data_types/tensor.h include/data_types/array.h include/data_types/tools.h src/data_types/tensor_test.cc include/data_types/matrix.h src/data_types/matrix.cc src/data_types/matrix_test.cc include/misc/exception.h src/misc/exception.cc include/nn/operators/operator.h src/nn/operators/operator.cc include/nn/operators/dense.h include/nn/operators/relu.h src/nn/operators/relu.cc include/derivative/operators.h src/derivative/operators_test.cc include/nn/operators/activation.h src/nn/operators/relu_test.cc include/misc/random.h src/misc/random.cc src/misc/misc_test.cpp include/derivative/functions.h src/nn/operators/op_test.cc)
add_executable(deeper_net ${SOURCE_FILES})

ADD_SUBDIRECTORY (gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(deeper_net gtest gtest_main)