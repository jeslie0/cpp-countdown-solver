#pragma once
#include <memory>
#include <ostream>
#include <vector>
#include <algorithm>
#include <optional>

// Define the type of expressions. An expression is one of the
// following:
// data Op = Add | Sub | Mul | Div deriving (Eq, Show)
// data Expr = Val Int | App Op Expr Expr deriving (Eq)

enum class Op {
    Add,
    Sub,
    Mul,
    Div
};

class Expr {
public:
    Expr(int val);
    Expr(std::shared_ptr<Expr> left, Op operation, std::shared_ptr<Expr> right);
    auto eval() const -> int;
    auto to_string() const -> std::string;

private:
    const int _val;
    const std::shared_ptr<Expr> _left;
    const std::optional<Op> _op;
    const std::shared_ptr<Expr> _right;
    auto set_val(const Expr& left, Op operation, const Expr& right) const -> int;
};

auto operator<<(std::ostream& out, const Expr& expr) -> std::ostream&;

auto valid(int left_num, Op operation, int right_num) -> bool;
