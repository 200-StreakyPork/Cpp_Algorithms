cmake_minimum_required(VERSION 3.14)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(Algorithms Chart/main/UCGraph.cpp Chart/include/Point.h Chart/main/Point.cpp Chart/include/UCGraph.h Chart/include/DCGraph.h Chart/main/DCGraph.cpp)