#ifndef INCLUDE_LIFEGAME_HPP_
#define INCLUDE_LIFEGAME_HPP_

#include <vector>
#include <cstdint>

class LifeGame {
public:
  LifeGame();
  LifeGame(int rows, int cols);

  const std::vector<std::vector<int>>& get_cells() const {
    return cells;
  }

  int get_rows() const {
    return rows;
  }

  int get_cols() const {
    return cols;
  }

  int get_generations() const {
    return generations;
  }

  int count_alive() const;

  void next_generation();

private:
  int rows{ 100 };
  int cols{ 100 };
  uint32_t generations{ 0 };
  std::vector<std::vector<int>> cells;

  void initialize_map(int rows, int cols);
};

#endif  // INCLUDE_LIFEGAME_HPP_
