#ifndef CONSTRAINT_INCREASE_HPP
#define CONSTRAINT_INCREASE_HPP

#include <vector>

#include "sudoku.hpp"

typedef struct IndexDiff
{
    int index;
    int diff;
} IndexDiff;

class ConstraintIncrease : public Sudoku::Constraint
{
public:
    ConstraintIncrease();
    ConstraintIncrease(ConstraintIncrease*, int diff);
	ConstraintIncrease(const ConstraintIncrease&) = delete;
	ConstraintIncrease(const ConstraintIncrease&&) = delete;
    void add(int index, int diff);
    void apply(Sudoku *dst);
    void print();
	void onAdded(Sudoku *, int index) override;
	SudokuResult onCollapsed(Sudoku *, int index, int value, SudokuNote note) override;

private:
    std::vector<IndexDiff> direction;
    // int maxDiff;
};

#endif /* CONSTRAINT_INCREASE_HPP */
