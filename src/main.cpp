#include <chrono>
#include <iostream>
#include <thread>

#include "simulation/Simulation.hpp"

int main() {
  try {
    bool simulate = true;
    simulation::Simulation sim({"x' = -y", "y' = x", "z' = 0"});
    std::thread sim_thrs(&simulation::Simulation::run, &sim, &simulate);
    sim.addEntity({
        0,
        -1,
        0,
    });
    sim.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    sim.stop();
    simulate = false;
    sim_thrs.join();
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
  return 0;
}
