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

// Generate and return the possible expressions formed from the input
// vector. These are formed "in order".
auto Solver::generate_expressions(const std::vector<int>& num_vec) -> std::vector<std::shared_ptr<Expr>>
{
    switch (num_vec.size())
    {
    case 0:
        return {};
    case 1:
        return { std::make_shared<Expr>(Expr(num_vec[0])) };
    default:
        std::vector<std::vector<std::shared_ptr<Expr>>> result;
        for (int indx = 1; indx < num_vec.size(); indx++)
        {
            const std::vector<int> left_nums(num_vec.begin(), num_vec.begin() + indx);
            const std::vector<int> right_nums(num_vec.begin() + indx, num_vec.end());
            const std::vector<std::shared_ptr<Expr>> left_exprs = generate_expressions(left_nums);
            const std::vector<std::shared_ptr<Expr>> right_exprs = generate_expressions(right_nums);
            for (const std::shared_ptr<Expr>& left_expr : left_exprs)
            {
                for (const std::shared_ptr<Expr>& right_expr : right_exprs)
                {
                    result.push_back(combine(left_expr, right_expr));
                }
            }
        }
        return flatten<std::shared_ptr<Expr>>(result);
    }
}

// Combine two expressions in valid ways.
auto Solver::combine(std::shared_ptr<Expr> left_ptr, std::shared_ptr<Expr> right_ptr) -> std::vector<std::shared_ptr<Expr>>
{
    std::vector<std::shared_ptr<Expr>> exprs {};

    if (valid(left_ptr->eval(), Op::Add, right_ptr->eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(Expr(left_ptr, Op::Add, right_ptr)));
    }
    if (valid(left_ptr->eval(), Op::Sub, right_ptr->eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(Expr(left_ptr, Op::Sub, right_ptr)));
    }
    if (valid(left_ptr->eval(), Op::Mul, right_ptr->eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(Expr(left_ptr, Op::Mul, right_ptr)));
    }
    if (valid(left_ptr->eval(), Op::Div, right_ptr->eval()))
    {
        exprs.emplace_back(std::make_shared<Expr>(Expr(left_ptr, Op::Div, right_ptr)));
    }

    return exprs;
}

// Generate all solutions.
auto Solver::generate_solutions() -> std::vector<std::shared_ptr<Expr>>
{
    // If any of the input numbers is a solution, add it to
    // _solutions.
    for (int num : _numbers)
    {
        if (num == _target)
        {
                    _solutions.emplace_back(std::make_shared<Expr>(Expr(num)));
        }
    }

    // Generate expressions from the permutations of every subsequence
    // of the input vector.
    std::vector<int> new_numbers = _numbers;
    for (auto& subvec : sub_sequences(new_numbers))
    {
        for (int num = 0; num < factorial(subvec.size()); num++)
        {
            for (const std::shared_ptr<Expr>& exp : generate_expressions(subvec))
            {
                if (exp->eval() == _target)
                {
                    _solutions.emplace_back(exp);
                }
            }
            std::next_permutation(subvec.begin(), subvec.end());
        }
    }

    return _solutions;
}
