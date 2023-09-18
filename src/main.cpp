
#include "sudoku.hpp"
#include "constraint_no_duplicate.hpp"

int main()
{
    Sudoku sudoku;
    ConstraintNoDuplicate *nodup = ConstraintNoDuplicate::create(&sudoku);
    nodup->standardSudoku(&sudoku);
    nodup->apply(&sudoku);
    if(!sudoku.read(stdin)) {
        printf("Error while reading sudoku\n");
        return 1;
    }
    List<Sudoku*> solution;
    Sudoku::solve(&sudoku, solution);
    printf("solution found: %d\n", solution.size());
    if(solution.size() > 1) {
        Sudoku::printSpecialSolution(solution);
        return 0;
    }
    for(int i=0; i<solution.size(); i++) {
        solution[i]->print(nullptr);
        printf("-------------------\n");
    }
    return 0;
}