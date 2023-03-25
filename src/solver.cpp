#include "expression.hpp"
#include "solver.hpp"
#include <algorithm>
#include <iostream>
#include "helper.hpp"

Solver::Solver(const std::vector<int> &numbers, const int target)
    : _numbers(numbers)
    , _target(target)
{
}

auto Solver::exprs(const std::vector<int> &num_vec) -> std::vector<Expr>
{
    switch (num_vec.size())
    {
    case 0:
        return {};
    case 1:
        return { Expr(num_vec[0]) };
    default:
        std::vector<std::vector<Expr>> result;
        for (const auto &pair : split<int>(num_vec))
        {
            std::vector<int> left_nums = pair.first;
            std::vector<int> right_nums = pair.second;
            std::vector<Expr> left_exprs = exprs(left_nums);
            std::vector<Expr> right_exprs = exprs(right_nums);
            for (Expr left_expr : left_exprs)
            {
                for (Expr right_expr : right_exprs)
                {
                    result.emplace_back(combine(left_expr, right_expr));
                }
            }
        }
        return flatten<Expr>(result);
    }
}

auto Solver::combine(Expr &left_expr, Expr &right_expr) -> std::vector<Expr>
{
    std::vector<Expr> exprs {};
    if (valid(left_expr.eval(), Op::Add, right_expr.eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(left_expr), Op::Add, std::make_shared<Expr>(right_expr));
    }
    if (valid(left_expr.eval(), Op::Sub, right_expr.eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(left_expr), Op::Sub, std::make_shared<Expr>(right_expr));
    }
    if (valid(left_expr.eval(), Op::Mul, right_expr.eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(left_expr), Op::Mul, std::make_shared<Expr>(right_expr));
    }
    if (valid(left_expr.eval(), Op::Div, right_expr.eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(left_expr), Op::Div, std::make_shared<Expr>(right_expr));
    }

    for (const Expr &expr : exprs)
    {
        if (expr.eval() == _target)
        {
            _solutions.push_back(expr);
        }
    }

    return exprs;
}

auto Solver::generate_solutions() -> std::vector<Expr>
{
    for (int num : _numbers)
    {
        if (num == _target)
        {
            _solutions.emplace_back(num);
        }
    }

    std::vector<int> new_numbers = _numbers;
    for (int num = 0; num < factorial(_numbers.size()); num++)
    {
        exprs(new_numbers);
        std::next_permutation(new_numbers.begin(), new_numbers.end());
    }

    return _solutions;
}
