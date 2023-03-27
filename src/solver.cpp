#include "expression.hpp"
#include "helper.hpp"
#include "solver.hpp"
#include <algorithm>
#include <iostream>
#include <memory>

Solver::Solver(const std::vector<int>& numbers, const int target)
    : _numbers(numbers)
    , _target(target)
{
}

auto Solver::generate_expressions(const std::vector<int>& num_vec) -> std::vector<Expr>
{
    switch (num_vec.size())
    {
    case 0:
        return {};
    case 1:
        return { Expr(num_vec[0]) };
    default:
        std::vector<std::vector<Expr>> result;
        // for (const auto& pair : split<int>(num_vec))
        for (int indx = 1; indx < num_vec.size(); indx++)
        {
            const std::vector<int> left_nums(num_vec.begin(), num_vec.begin() + indx);
            const std::vector<int> right_nums(num_vec.begin() + indx, num_vec.end());
            const std::vector<Expr> left_exprs = generate_expressions(left_nums);
            const std::vector<Expr> right_exprs = generate_expressions(right_nums);
            for (const Expr& left_expr : left_exprs)
            {
                for (const Expr& right_expr : right_exprs)
                {
                    result.push_back(combine(left_expr, right_expr));
                }
            }
        }
        return flatten<Expr>(result);
    }
}

inline auto Solver::combine(const Expr& left_expr, const Expr& right_expr) -> std::vector<Expr>
{
    std::vector<Expr> exprs {};
    std::shared_ptr<Expr> left_ptr = std::make_shared<Expr>(left_expr);
    std::shared_ptr<Expr> right_ptr = std::make_shared<Expr>(right_expr);

    if (valid(left_expr.eval(), Op::Add, right_expr.eval()))
    {
        exprs.emplace_back(Expr(left_ptr, Op::Add, right_ptr));
    }
    if (valid(left_expr.eval(), Op::Sub, right_expr.eval()))
    {
        exprs.emplace_back(Expr(left_ptr, Op::Sub, right_ptr));
    }
    if (valid(left_expr.eval(), Op::Mul, right_expr.eval()))
    {
        exprs.emplace_back(Expr(left_ptr, Op::Mul, right_ptr));
    }
    if (valid(left_expr.eval(), Op::Div, right_expr.eval()))
    {
        exprs.emplace_back(Expr(left_ptr, Op::Div, right_ptr));
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
    for (auto& subvec : subVectors(new_numbers))
    {
        for (int num = 0; num < factorial(subvec.size()); num++)
        {
            for (const Expr& exp : generate_expressions(subvec))
            {
                if (exp.eval() == _target)
                {
                    _solutions.emplace_back(exp);
                }
            }
            std::next_permutation(subvec.begin(), subvec.end());
        }
    }

    return _solutions;
}
