#ifndef SUDOKU_CONSTRAINT_HPP
#define SUDOKU_CONSTRAINT_HPP

#include "sudoku.hpp"

class Constraint
{
public:
    virtual void onCollaped(Sudoku *, int index, int value, SudokuNote note);
};

#endif /* SUDOKU_CONSTRAINT_HPP */