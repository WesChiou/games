#ifndef _INCLUDE_MINESWEEPERMAP_HPP_
#define _INCLUDE_MINESWEEPERMAP_HPP_

#include <vector>

#include "MinesweeperCell.hpp"

class MinesweeperMap {
public:
  MinesweeperMap(int rows, int cols, int mines) {
    set_map(rows, cols, mines);
  };

  void reset() {
    set_map(this->rows, this->cols, this->mines);
  };

  void reset(int rows, int cols, int mines) {
    set_map(rows, cols, mines);
  };

  const std::vector<std::vector<MinesweeperCell>>& get_cells() {
    return cells;
  };

private:
  int rows{9};
  int cols{9};
  int mines{10};
  std::vector<std::vector<MinesweeperCell>> cells;

  void set_map(int rows, int cols, int mines);
};

#endif
