#include "constraint_no_duplicate.hpp"

ConstraintNoDuplicate::ConstraintNoDuplicate()
{}

void ConstraintNoDuplicate::addNeigbour(int index)
{
    for(auto neighbour : neighbours) {
        if(index == neighbour) return;
    }
    neighbours.push_back(index);
}

SudokuResult ConstraintNoDuplicate::onCollapsed(Sudoku *sudoku, int collapsedIndex, int value, SudokuNote note)
{
    bool changed = false;
    SudokuNote inverse = ~note;
    for(auto index : neighbours) {
        if(sudoku->isIgnored(index)) continue;
        int oldValue = sudoku->note[index];
        if(oldValue & SudokuNoteOk) continue;
        int result = oldValue & inverse;
        changed |= oldValue != result;
        if((result & SudokuNoteAll) == 0) return SudokuResultError;
        sudoku->note[index] = result;
    }
    return changed ? SudokuResultOk : SudokuResultUnchanged;
}

ConstraintNoDuplicate *ConstraintNoDuplicate::create(Sudoku *sudoku)
{
    return new ConstraintNoDuplicate[sudoku->getSize()];
}

void ConstraintNoDuplicate::apply(Sudoku *dst)
{
    for(int i = 0; i < dst->getSize(); i++) {
        dst->addConstraint(i, &this[i]);
    }
}

GroupGenerator::GroupGenerator(int _groupCount, int _groupSize)
    : groupCount(_groupCount), groupSize(_groupSize)
{}

void ConstraintNoDuplicate::addRelative(Sudoku *sudoku, int ox, int oy, int dx, int dy)
{
    int ix = ox + dx;
    int iy = oy + dy;
    if(ix < 0 || ix >= sudoku->getDimension()) return;
    if(iy < 0 || iy >= sudoku->getDimension()) return;
    this[oy * sudoku->getDimension() + ox].addNeigbour(iy * sudoku->getDimension() + ix);
}

void ConstraintNoDuplicate::inAdjacent(Sudoku *sudoku)
{
    for(int y = 0; y < sudoku->getDimension(); y++) {
        for(int x = 0; x < sudoku->getDimension(); x++) {
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    if(dx == 0 && dy == 0) continue;
                    addRelative(sudoku, x, y, dx, dy);
                }
            }
        }
    }
}

void ConstraintNoDuplicate::inHorseMove(Sudoku *sudoku)
{
    for(int y=0; y<sudoku->getDimension(); y++) {
        for(int x=0; x<sudoku->getDimension(); x++) {
            addRelative(sudoku, x, y, -2, -1);
            addRelative(sudoku, x, y, -1, -2);
            addRelative(sudoku, x, y,  2, -1);
            addRelative(sudoku, x, y,  1, -2);
            addRelative(sudoku, x, y,  2,  1);
            addRelative(sudoku, x, y,  1,  2);
            addRelative(sudoku, x, y, -2,  1);
            addRelative(sudoku, x, y, -1,  2);
        }
    }
}
