#include "expression.hpp"
#include "solver.hpp"
#include <iostream>
#include <vector>

auto main() -> int
{
    std::vector<int> nums { 1, 3, 7, 10, 25, 50 };
    Solver solutions = Solver(nums, 765);

    std::vector<Expr> test = solutions.generate_solutions();
    for (Expr expr : test)
    {
        std::cout << expr.to_string() << " | " << expr.eval() << std::endl;
    }

    return 0;
}
