#include <functional>
#include <random>
#include "../include/LifeGame.hpp"

LifeGame::LifeGame()
: rows(100), cols(100) {
  initialize_map(rows, cols);
}

LifeGame::LifeGame(int rows, int cols) {
  this->rows = (rows > 0 && rows <= 999) ? rows : 100;
  this->cols = (cols > 0 && cols <= 999) ? cols : 100;
  initialize_map(rows, cols);
}

int LifeGame::count_alive() const {
  int count{ 0 };

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      count += cells[i][j];
    }
  }

  return count;
}

void LifeGame::next_generation() {
  std::vector<std::vector<int>> next_generation(rows, std::vector<int>(cols, 0));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int neighbors{ 0 };

      for (int row = i - 1; row <= i + 1; row++) {
        for (int col = j - 1; col <= j + 1; col++) {
          if (row >= 0
            && row < rows
            && col >= 0
            && col < cols
            && !(row == i && col == j)  // [i][j] is itself, not its neighbor
          ) {
            neighbors += cells[row][col];
          }
        }
      }

      // Conway's game of life rules:
      const int current{ cells[i][j] };

      if (current && neighbors < 2) {
        next_generation[i][j] = 0;
      } else if (current && (neighbors == 2 || neighbors == 3)) {
        next_generation[i][j] = current;  // or: next_generation[i][j] = true;
      } else if (current && neighbors > 3) {
        next_generation[i][j] = 0;
      } else if (!current && neighbors == 3) {
        next_generation[i][j] = 1;
      }
    }
  }

  cells = next_generation;

  generations++;
}

void LifeGame::initialize_map(int rows, int cols) {
  auto gen_random_bool = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());

  for (int i = 0; i < rows; ++i) {
    std::vector<int> curr_row;

    for (int j = 0; j < cols; ++j) {
      curr_row.push_back(gen_random_bool());
    }

    cells.push_back(curr_row);
  }
}
