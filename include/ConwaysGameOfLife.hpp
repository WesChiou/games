#ifndef INCLUDE_CONWAYSGAMEOFLIFE_HPP_
#define INCLUDE_CONWAYSGAMEOFLIFE_HPP_

#include <vector>
#include <cstdint>

using Time = uint32_t;

enum class Speed {
  X1 = 1,
  X4 = 4,
  X8 = 8,
};

class ConwaysGameOfLife {
public:
  ConwaysGameOfLife() {
    initialize_world(48, 64);
  }

  ConwaysGameOfLife(int rows, int cols) {
    initialize_world(rows, cols);
  }

private:
  std::vector<std::vector<int>> cells;
  Time per_generation{1000/4};
  Speed speed{Speed::X1};
  uint32_t generations{0};

  void initialize_world(int rows, int cols);

  void next_generation();
};

#endif  // INCLUDE_CONWAYSGAMEOFLIFE_HPP_
