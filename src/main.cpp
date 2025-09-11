#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <vector>

#include "backend/parser.hpp"
#include "gui/App/App.hpp"

float f(float x, float y) {
  return std::sin(x * x + y) * std::exp(y / x);
}

using namespace std::chrono_literals;
using clk = std::chrono::steady_clock;

volatile float sink;

int main(int argc, char** argv) {
  App app(argc, argv);
  return app.exec();
  // auto str = std::string("sin(x^2+y)*exp(y/x)");
  // try {
  //   auto parser = parser::Parser();
  //   parser.m_vars.addVariable("x");
  //   parser.m_vars.addVariable("y");
  //   auto expr = parser.parseExpr(str);
  //   float x, y;
  //   std::cin >> x >> y;
  //   auto vars = std::vector<float>{x, y};
  //   auto start = clk::now();
  //   for (size_t i = 0; i < 1'000'000; ++i) { sink += f(x + i, y); }
  //   auto end = clk::now();
  //   std::cout << (end - start) / 1ms << '\n';
  //   start = clk::now();
  //   for (size_t i = 0; i < 1'000'000; ++i) {
  //     sink += expr->eval(vars);
  //     vars[x] += i;
  //   }
  //   end = clk::now();
  //   std::cout << (end - start) / 1ms << '\n';
  // } catch (std::exception& e) { std::cout << e.what(); }
  // return 0;
}