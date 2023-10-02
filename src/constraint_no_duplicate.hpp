#pragma once

#include <vector>

#include "sudoku.hpp"
#include "group_generator.hpp"

class ConstraintNoDuplicate : public Sudoku::Constraint
{
public:
    void addNeigbour(int index);
    SudokuResult onCollapsed(Sudoku *, int index, int value, SudokuNote note) override;
    void apply(Sudoku *dst);
    void standardSudoku(Sudoku *sudoku, int ox = 0, int oy = 0);
    void inStandardBlock(Sudoku *sudoku, int ox = 0, int oy = 0);
    void inVerticalLine(Sudoku *sudoku, int ox = 0, int oy = 0);
    void inHorizontalLine(Sudoku *sudoku, int ox = 0, int oy = 0);
    void inAdjacent(Sudoku *sudoku);
    void inHorseMove(Sudoku *sudoku);

    void addRelative(Sudoku *sudoku, int ox, int oy, int dx, int dy);

    static ConstraintNoDuplicate *create(Sudoku *sudoku);

private:
    ConstraintNoDuplicate();
    std::vector<int> neighbours;
};
