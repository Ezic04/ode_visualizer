cmake -G "Ninja" -B build -S . ^
  && cmake --build build ^
  && .\build\ode_visualizer.exe
