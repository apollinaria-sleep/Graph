cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_library(graph graph.h graph.cpp findMST.cpp)
add_executable(graph_test graph_test.cpp)
target_link_libraries(graph_test graph)
