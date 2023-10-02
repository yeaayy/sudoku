
#include <iostream>
#include <vector>

#include "sudoku.hpp"
#include "constraint_no_duplicate.hpp"

int main()
{
    Sudoku sudoku;
    ConstraintNoDuplicate *nodup = ConstraintNoDuplicate::create(&sudoku);
    nodup->standardSudoku(&sudoku);
    nodup->apply(&sudoku);
    if(!(std::cin >> sudoku)) {
        std::cout << "Error while reading sudoku\n";
        return 1;
    }
    std::vector<Sudoku*> solution;
    Sudoku::solve(&sudoku, solution);
    std::cout << "solution found: " << solution.size() << "\n";
    if(solution.size() > 1) {
        Sudoku::printSpecialSolution(solution);
        return 0;
    }
    for(std::size_t i=0; i<solution.size(); i++) {
        solution[i]->print(std::cout, nullptr);
        std::cout << solution[i]->bar();
        delete solution[i];
    }
    int something;
    std::cin >> something;
    return 0;
}