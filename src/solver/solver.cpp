#include "solver/solver.hpp"

#include "utility/utility.hpp"

namespace solver {

State euler(const System &system, const State &vars, size_t ind_idx, FloatType step) {
  assertm(system.size() == vars.size(), "System and state size mismatch");
  State new_state;
  for (size_t i = 0; i < system.size(); ++i) {
    new_state[i] = vars[i] + step * system[i]->eval(vars);
  }
  return std::move(new_state);
}

// State heun(const System &system, const State &vars, FloatType t, FloatType step) {
// assertm(system.size() == vars.size(), "System and state size mismatch");
// FloatType x_new = euler(f, x, t, step, vars);
// t += step;
// return x + step / 2 * (x_new + f->eval(vars));
// }

} // namespace solver