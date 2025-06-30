#include "tests/eval_test.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "expr/dynamic.hpp"
#include "expr/lambda.hpp"
#include "expr/stack.hpp"
#include "utility/utility.hpp"

namespace d = expr::dynamic;
namespace l = expr::lambda;
namespace s = expr::stack;

namespace tests {

void benchmark_exprs() {
  constexpr int N = 1'000'000;

  std::vector<FloatType> vars = {3.14};

  // ----------- SMALL ----------- (x+1)*sin(2x)
  l::ExprPtr le = l::make_binary(
      l::BinaryOpType::Mul, l::make_binary(l::BinaryOpType::Add, l::make_var(0), l::makeConst(1.0)),
      l::makeUnary(l::UnaryOpType::Sin, l::make_binary(l::BinaryOpType::Mul, l::makeConst(2.0), l::make_var(0))));

  d::ExprPtr dx = std::make_shared<d::Var>(0);
  d::ExprPtr done = std::make_shared<d::Const>(1.0);
  d::ExprPtr dtwo = std::make_shared<d::Const>(2.0);
  d::ExprPtr dx_plus_1 = std::make_shared<d::BinaryOp>(d::BinaryOpType::kAdd, dx, done);
  d::ExprPtr dtwo_x = std::make_shared<d::BinaryOp>(d::BinaryOpType::kMul, dtwo, dx);
  d::ExprPtr dsin_2x = std::make_shared<d::UnaryOp>(d::UnaryOpType::kSin, dtwo_x);
  d::ExprPtr dexpr = std::make_shared<d::BinaryOp>(d::BinaryOpType::kMul, dx_plus_1, dsin_2x);

  s::Program sprog = {s::Node(s::Op::Var, (size_t)0),
                      s::Node(s::Op::Const, FloatType(1.0)),
                      s::Node(s::Op::Add),
                      s::Node(s::Op::Const, FloatType(2.0)),
                      s::Node(s::Op::Var, size_t(0)),
                      s::Node(s::Op::Mul),
                      s::Node(s::Op::Sin),
                      s::Node(s::Op::Mul)};

  // ----------- MEDIUM ----------- (x+1)*sin(2x)*exp(x) + log(x+1)^2
  l::ExprPtr lmed = l::make_binary(
      l::BinaryOpType::Add, l::make_binary(l::BinaryOpType::Mul, le, l::makeUnary(l::UnaryOpType::Exp, l::make_var(0))),
      l::makeIntPow(
          l::makeUnary(l::UnaryOpType::Log, l::make_binary(l::BinaryOpType::Add, l::make_var(0), l::makeConst(1.0))),
          2));

  d::ExprPtr dlog_x1 = std::make_shared<d::UnaryOp>(d::UnaryOpType::kLog, dx_plus_1);
  d::ExprPtr dpow_log = std::make_shared<d::IntPow>(dlog_x1, 2);
  d::ExprPtr dexp_x = std::make_shared<d::UnaryOp>(d::UnaryOpType::kExp, dx);
  d::ExprPtr dlpart = std::make_shared<d::BinaryOp>(d::BinaryOpType::kMul, dexpr, dexp_x);
  d::ExprPtr dmed = std::make_shared<d::BinaryOp>(d::BinaryOpType::kAdd, dlpart, dpow_log);

  s::Program smed = {
      s::Node(s::Op::Var, (size_t)0), // x
      s::Node(s::Op::Const, FloatType(1.0)),
      s::Node(s::Op::Add), // x+1
      s::Node(s::Op::Const, FloatType(2.0)),
      s::Node(s::Op::Var, (size_t)0),
      s::Node(s::Op::Mul), // 2x
      s::Node(s::Op::Sin), // sin(2x)
      s::Node(s::Op::Mul), // (x+1)*sin(2x)
      s::Node(s::Op::Var, (size_t)0),
      s::Node(s::Op::Exp), // exp(x)
      s::Node(s::Op::Mul), // (...) * exp(x)
      s::Node(s::Op::Var, (size_t)0),
      s::Node(s::Op::Const, FloatType(1.0)),
      s::Node(s::Op::Add),               // x+1
      s::Node(s::Op::Log),               // log(x+1)
      s::Node(s::Op::PowInt, size_t(2)), // (...)^2
      s::Node(s::Op::Add)                // final +
  };

  auto run_lambda = [&](auto &expr) {
    volatile FloatType sum = 0.0;
    for (int i = 0; i < N; ++i) sum += expr->eval(vars);
    return sum;
  };

  auto run_virtual = [&](auto &expr) {
    volatile FloatType sum = 0.0;
    for (int i = 0; i < N; ++i) sum += expr->eval(vars);
    return sum;
  };

  auto run_stack = [&](const s::Program &p) {
    volatile FloatType sum = 0.0;
    for (int i = 0; i < N; ++i) sum += s::eval(p, vars);
    return sum;
  };

  auto bench = [&](const char *label, auto &&fn) {
    auto start = std::chrono::high_resolution_clock::now();
    fn();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << label << " " << std::chrono::duration<FloatType>(end - start).count() << "s\n";
  };

  bench("[lambda/small]", [&] { run_lambda(le); });
  bench("[virtual/small]", [&] { run_virtual(dexpr); });
  bench("[stack/small]", [&] { run_stack(sprog); });

  bench("[lambda/med]", [&] { run_lambda(lmed); });
  bench("[virtual/med]", [&] { run_virtual(dmed); });
  bench("[stack/med]", [&] { run_stack(smed); });
}

void variable_lookup_perf() {
  constexpr int N = 1'000'000;
  const std::vector<FloatType> lvars = {3.14, 3.14, 3.14, 3.14};
  const std::unordered_map<std::string, FloatType> vvars = {{"x", 3.14}, {"y", 3.14}, {"z", 3.14}, {"t", 3.14}};

  volatile FloatType sum_vec = 0.0;
  volatile FloatType sum_map = 0.0;

  // Vector access
  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) sum_vec += lvars[0];
  auto t2 = std::chrono::high_resolution_clock::now();

  // Map access
  auto t3 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) sum_map += vvars.at("x");
  auto t4 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<FloatType> dvec = t2 - t1;
  std::chrono::duration<FloatType> dmap = t4 - t3;

  std::cout << "Vector access time: " << dvec.count() << " s\n";
  std::cout << "Map access time:    " << dmap.count() << " s\n";
  std::cout << "Ratio (map / vec):  " << (dmap / dvec) << "\n";
}

} // namespace tests