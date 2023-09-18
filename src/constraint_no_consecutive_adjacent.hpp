#pragma once

#include "sudoku.hpp"

class ConstraintNoConsecutiveAdjacent : public Sudoku::Constraint
{
public:
    ConstraintNoConsecutiveAdjacent() {}
	ConstraintNoConsecutiveAdjacent(const ConstraintNoConsecutiveAdjacent&) = delete;
	ConstraintNoConsecutiveAdjacent(const ConstraintNoConsecutiveAdjacent&&) = delete;
	void onAdded(Sudoku *, int index) override;
	SudokuResult onCollapsed(Sudoku *, int index, int value, SudokuNote note) override;
    int collapse(Sudoku *sudoku, int x, int y, int dx, int dy, SudokuNote inverse);
	void apply(Sudoku *dst);
};
