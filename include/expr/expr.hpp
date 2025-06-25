#pragma once
#include "expr/dynamic.hpp"
#include "expr/parser.hpp"

namespace expr {
using Expr = dynamic::Expr;
using ExprPtr = dynamic::ExprPtr;

using UnaryOpType = dynamic::UnaryOpType;
using BinaryOpType = dynamic::BinaryOpType;

using Const = dynamic::Const;
using Var = dynamic::Var;
using IntPow = dynamic::IntPow;
using UnaryOp = dynamic::UnaryOp;
using BinaryOp = dynamic::BinaryOp;

using VaribleMap = dynamic::VariableMap;
using ParserException = dynamic::ParserException;
using dynamic::parseExpr;

} // namespace expr
