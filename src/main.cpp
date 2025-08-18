#include "simulation/Simulation.hpp"

int main() {
  simulation::Simulation sim;
  sim.addEntity({ 0.0f, 0.0f, 0.0f });
  sim.run();
}