cmake_minimum_required(VERSION 3.13)
project(EXPRESSION)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)