
add_library(sudoku_base STATIC
    constraint_increase.cpp
    constraint_no_duplicate.cpp
    constraint_no_consecutive_adjacent.cpp
    constraint_standard_shifted.cpp
    group_generator.cpp
    sudoku.cpp
)

if(HAS_HISTORY)
    target_compile_definitions(sudoku_base PRIVATE HAS_HISTORY)
endif()

target_link_libraries(sudoku PUBLIC sudoku_base)
