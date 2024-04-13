
#include <fstream>
#include <vector>

#include "sudoku.hpp"
#include "constraint_no_duplicate.hpp"
#include "constraint_no_consecutive_adjacent.hpp"

int main()
{
    Sudoku sudoku(21);
    ConstraintNoDuplicate *nodup = ConstraintNoDuplicate::create(&sudoku);
    nodup->standardSudoku(&sudoku, 6, 0);
    nodup->standardSudoku(&sudoku, 0, 6);
    nodup->standardSudoku(&sudoku, 12, 6);
    nodup->standardSudoku(&sudoku, 6, 12);
    nodup->inAdjacent(&sudoku);
    nodup->inHorseMove(&sudoku);
    nodup->apply(&sudoku);
    (new ConstraintNoConsecutiveAdjacent())->apply(&sudoku);
    if(!(std::cin >> sudoku)) {
        std::cout << "Error while reading input file\n";
        return 1;
    }
    std::vector<Sudoku*> solution;
    Sudoku::solve(&sudoku, solution, 2);
    if(solution.size() > 1) {
        Sudoku::printSpecialSolution(solution);
        return 0;
    }
    std::cout << "solution found: " << solution.size() << "\n";
    for(std::size_t i=0; i<solution.size(); i++) {
        solution[i]->print(std::cout, nullptr);
        std::cout << solution[i]->bar();
    }
    return 0;
}