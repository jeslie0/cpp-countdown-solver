#include "expression.hpp"
#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

Expr::Expr(int val)
    : _val(val)
    , _op(std::nullopt)
{};

Expr::Expr(std::shared_ptr<Expr> left, Op operation, std::shared_ptr<Expr> right)
    : _val(set_val(*left, operation, *right))
    , _left(std::move(left))
    , _op(operation)
    , _right(std::move(right)) {};

auto Expr::eval() const -> int
{
    return _val;
}

auto Expr::to_string() const -> std::string
{
    if (_op.has_value())
    {
        switch (_op.value())
        {
        case Op::Add:
            return "(" + _left->to_string() + "+" + _right->to_string() + ")";
        case Op::Sub:
            return "(" + _left->to_string() + "-" + _right->to_string() + ")";
        case Op::Mul:
            return "(" + _left->to_string() + "*" + _right->to_string() + ")";
        case Op::Div:
            return "(" + _left->to_string() + "/" + _right->to_string() + ")";
        default:
            return "";
        }
    }
    else
    {
        return std::to_string(_val);
    }
}

auto Expr::set_val(const Expr &left, Op operation, const Expr &right) const -> int
{
    switch (operation)
    {
    case Op::Add:
        return left._val + right._val;
    case Op::Sub:
        return left._val - right._val;
    case Op::Mul:
        return left._val * right._val;
    case Op::Div:
        return left._val / right._val;
    }
}

auto valid(int left_num, Op operation, int right_num) -> bool
{
    switch (operation)
    {
    case Op::Add:
        return left_num <= right_num && left_num != 0 && right_num != 0;
    case Op::Sub:
        return left_num > right_num;
    case Op::Mul:
        return left_num <= right_num && left_num != 1 && left_num != 0 && right_num != 1 && right_num != 0;
    case Op::Div:
        return left_num % right_num == 0 && right_num != 1;
    }
}
