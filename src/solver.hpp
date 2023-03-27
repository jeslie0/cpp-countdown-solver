#pragma once
#include <memory>
#include "expression.hpp"
#include <vector>

class Solver
{
public:
    Solver(const std::vector<int> &numbers, int target);
    auto generate_solutions() -> std::vector<std::shared_ptr<Expr>>;

private:
    const std::vector<int> &_numbers;
    const int _target;

  std::vector<std::shared_ptr<Expr>> _solutions = {};
  auto generate_expressions(const std::vector<int> &vec) -> std::vector<std::shared_ptr<Expr>>;
  auto combine(std::shared_ptr<Expr> left_expr, std::shared_ptr<Expr> right_expr) -> std::vector<std::shared_ptr<Expr>>;
};
