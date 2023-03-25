#include "expression.hpp"
#include "solver.hpp"
#include <iostream>
#include <vector>

auto main() -> int
{
    std::vector<int> nums { 10, 25, 50, 75, 100, 4, 4};
    Solver solutions = Solver(nums, 563);

    std::vector<Expr> test = solutions.generate_solutions();
    for (const Expr& expr : test)
    {
        std::cout << expr.to_string() << " | " << expr.eval() << std::endl;
    }

    return 0;
}
