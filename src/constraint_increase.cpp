#include "constraint_increase.hpp"

ConstraintIncrease::ConstraintIncrease()
{
}

ConstraintIncrease::ConstraintIncrease(ConstraintIncrease *src, int diff)
{
    for(auto &item : src->direction) {
        add(item.index, item.diff - diff);
    }
}

void ConstraintIncrease::add(int index, int diff)
{
    IndexDiff item = {index, diff};
    direction.push_back(item);
}

void ConstraintIncrease::apply(Sudoku *dst)
{
    for(auto &dir : direction) {
        if(dir.diff == 0) {
            dst->addConstraint(dir.index, this);
        } else {
            dst->addConstraint(dir.index, new ConstraintIncrease(this, dir.diff));
        }
    }
}

void ConstraintIncrease::print()
{
    for(auto &dir : direction) {
        int index = dir.index;
    }
}

void ConstraintIncrease::onAdded(Sudoku *sudoku, int index)
{
    int above = 0;
    int bellow = 0;
    for(auto &item : direction) {
        if(item.diff < 0) bellow++;
        if(item.diff > 0) above++;
    }
    int bit = SudokuNoteAll >> above & SudokuNoteAll << bellow;
    sudoku->note[index] &= bit;
}

SudokuResult ConstraintIncrease::onCollapsed(Sudoku *sudoku, int index, int value, SudokuNote note)
{
    SudokuResult fresult = SudokuResultUnchanged;
    for(auto &item : direction) {
        int oldValue = sudoku->note[item.index];
        if(oldValue & SudokuNoteOk) continue;

        int bit;
        if(item.diff < 0) bit = SudokuNoteAll >> (8 - value - item.diff);
        else if(item.diff > 0) bit = SudokuNoteAll << (value + item.diff);
        else continue;

        int newValue = (oldValue & ~SudokuNoteAll) | (oldValue & bit & SudokuNoteAll);

        if(oldValue != newValue) {
            fresult = SudokuResultOk;
        }
        if((newValue & SudokuNoteAll) == 0) {
            return SudokuResultError;
        }
        sudoku->note[item.index] = newValue;
    }
    return fresult;
}