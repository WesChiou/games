#include "MinesweeperMap.hpp"

#include <iostream> // TODO: remove
#include <random>

void MinesweeperMap::set_map(int rows, int cols, int mines) {
  // 9 <= rows <= 24
  // 9 <= cols <= 30
  // 10 <= mines <= size * 0.8

  this->rows = rows >= 9 && rows <= 24 ? rows : (rows < 9 ? 9 : 24);
  this->cols = cols >= 9 && cols <= 30 ? cols : (cols < 9 ? 9 : 30);

  int max_mines = this->rows * this->cols * 0.8;
  this->mines = mines >= 10 && mines <= max_mines ? mines : (mines < 10 ? 10 : max_mines);

  // Set mines randomly.

  cells = std::vector<std::vector<MinesweeperCell>>(
    this->rows,
    std::vector<MinesweeperCell>(this->cols, false)
  );

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist_r(0, this->rows - 1);
  std::uniform_int_distribution<int> dist_c(0, this->cols - 1);
  int i = this->mines;
  while (i--) {
    int r = dist_r(rng);
    int c = dist_c(rng);
    if (!cells[r][c].is_mine()) {
      cells[r][c] = MinesweeperCell(true);
    } else {
      i++;
    }
  }

  // Set number of around mines for every cell.

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      int count = 0;
      for (int ii = -1; ii <= 1; ii++) {
        for (int jj = -1; jj <= 1; jj++) {
          if (i + ii >= 0 && i + ii < this->rows && j + jj >= 0 && j + jj < this->cols) {
            count += cells[i + ii][j + jj].is_mine();
          }
        }
      }
      cells[i][j].set_around_mines_num(count);
    }
  }

  for (auto r : cells) {
    for (auto c : r) {
      std::cout << (c.is_mine() ? "*" : std::to_string(c.around_mines_num())) << " ";
    }
    std::cout << "\n";
  }
}
