#pragma once
#include "expression.hpp"
#include <vector>

class Solver
{
public:
    Solver(const std::vector<int> &numbers, int target);
    auto generate_solutions() -> std::vector<Expr>;

private:
    const std::vector<int> &_numbers;
    const int _target;

    std::vector<Expr> _solutions = {};
    auto generate_expressions(const std::vector<int> &vec) -> std::vector<Expr>;
    auto combine(const Expr &left_expr, const Expr &right_expr) -> std::vector<Expr>;
};
