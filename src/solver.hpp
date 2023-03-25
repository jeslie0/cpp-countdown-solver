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
    auto exprs(const std::vector<int> &vec) -> std::vector<Expr>;
    auto combine(Expr &left_expr, Expr &right_expr) -> std::vector<Expr>;
};
