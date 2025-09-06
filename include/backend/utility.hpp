#pragma once
#include <cassert>

#define assertm(exp, msg) assert(((msg), exp))

namespace expr {
/**
 * Computes x raised to integer power n.
 * @param x base
 * @param n exponent
 * @return x^n
 */
inline float intPow(double x, int n) {
  if (n == 0) { return 1.0; }
  if (n < 0) { return 1.0 / intPow(x, -n); }
  double result = 1.0;
  while (n > 0) {
    if (n & 1) result *= x;
    x *= x;
    n >>= 1;
  }
  return result;
}

}  // namespace expr