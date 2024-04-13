cmake_minimum_required(VERSION 3.15)
project(Tutorial)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(MAIN "File that contain main function" "src/main.cpp")
option(HAS_HISTORY "Record change history" OFF)

add_compile_options("$<BUILD_INTERFACE:-Wall;-ggdb>")

add_executable(sudoku
    ${MAIN}
)

add_subdirectory(src)
