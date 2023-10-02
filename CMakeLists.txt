cmake_minimum_required(VERSION 3.15)
project(Tutorial)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options("$<BUILD_INTERFACE:-Wall;-ggdb>")

add_subdirectory(src bin)
