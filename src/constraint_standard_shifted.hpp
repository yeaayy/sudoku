#pragma once

#include "sudoku.hpp"
#include "group_generator.hpp"

class ConstraintNoDuplicate;

#define GENERATE_CLASS(__NAME__) \
class __NAME__:public GroupGenerator{public: __NAME__(Sudoku *_sudoku, int _ox, int _oy);void getGroup(int *dst, int y);private:Sudoku *sudoku;int ox, oy;}

GENERATE_CLASS(GGStandardBlock);
GENERATE_CLASS(GGHorizontal);
GENERATE_CLASS(GGVertical);

#undef GENERATE_CLASS
