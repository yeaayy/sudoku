#include "constraint_standard_shifted.hpp"

#include "sudoku.hpp"
#include "constraint_no_duplicate.hpp"

GGStandardBlock::GGStandardBlock(Sudoku *_sudoku, int _ox, int _oy) : GroupGenerator(9, 9), sudoku(_sudoku), ox(_ox), oy(_oy)
{}

void GGStandardBlock::getGroup(int *dst, int y) {
    for(int x = 0; x < 9; x++) {
        dst[x] = sudoku->getIndex(y / 3 * 3 + x / 3 + oy, y % 3 * 3 + x % 3 + ox);
    }
}

GGHorizontal::GGHorizontal(Sudoku *_sudoku, int _ox, int _oy) : GroupGenerator(9, 9), sudoku(_sudoku), ox(_ox), oy(_oy)
{}

void GGHorizontal::getGroup(int *dst, int y) {
    for(int x = 0; x < 9; x++) {
        dst[x] = sudoku->getIndex(y + ox, x + oy);
    }
}

GGVertical::GGVertical(Sudoku *_sudoku, int _ox, int _oy) : GroupGenerator(9, 9), sudoku(_sudoku), ox(_ox), oy(_oy)
{}

void GGVertical::getGroup(int *dst, int y) {
    for(int x = 0; x < 9; x++) {
        dst[x] = sudoku->getIndex(x + ox, y + oy);
    }
}

void ConstraintNoDuplicate::inStandardBlock(Sudoku *sudoku, int ox, int oy)
{
    GGStandardBlock(sudoku, ox, oy).apply(this);
}

void ConstraintNoDuplicate::inVerticalLine(Sudoku *sudoku, int ox, int oy)
{
    GGVertical(sudoku, ox, oy).apply(this);
}

void ConstraintNoDuplicate::inHorizontalLine(Sudoku *sudoku, int ox, int oy)
{
    GGHorizontal(sudoku, ox, oy).apply(this);
}

void ConstraintNoDuplicate::standardSudoku(Sudoku *sudoku, int ox, int oy) {
    inStandardBlock(sudoku, ox, oy);
    inVerticalLine(sudoku, ox, oy);
    inHorizontalLine(sudoku, ox, oy);
}
