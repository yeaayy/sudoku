#include "constraint_no_consecutive_adjacent.hpp"

void ConstraintNoConsecutiveAdjacent::onAdded(Sudoku *sudoku, int index)
{
    ;
}

int ConstraintNoConsecutiveAdjacent::collapse(Sudoku *sudoku, int x, int y, int dx, int dy, SudokuNote inverse)
{
    int index = sudoku->getIndex(x + dx, y + dy);
    if(index == -1) return 1;
    if(sudoku->isIgnored(index)) return 1;
    int oldNote = sudoku->note[index];
    if(oldNote & SudokuNoteOk) return 1;
    int newNote = oldNote & inverse;
    if((newNote & SudokuNoteAll) == 0) return -1;
    sudoku->note[index] = newNote;
    return oldNote == newNote;
}

SudokuResult ConstraintNoConsecutiveAdjacent::onCollapsed(Sudoku *sudoku, int index, int value, SudokuNote note)
{
    SudokuNote inverse = ~((value == 8 ? 0 : sudoku->value2note(value + 1)) | (value == 0 ? 0 : sudoku->value2note(value - 1)));
    int x = index % sudoku->getDimension();
    int y = index / sudoku->getDimension();
    int result = 1;
    for(int dy=-1; dy<=1; dy++) {
        for(int dx=-1; dx<=1; dx++) {
            if(dx == 0 && dy == 0) continue;
            if(dx != 0 && dy != 0) continue;
            result *= collapse(sudoku, x, y, dx,  dy, inverse);
            if(result == -1) return SudokuResultError;
        }
    }
    return result == 0 ? SudokuResultOk : SudokuResultUnchanged;
}

void ConstraintNoConsecutiveAdjacent::apply(Sudoku *dst)
{
    for(int i=0; i<dst->getSize(); i++) {
        dst->addConstraint(i, this);
    }
}