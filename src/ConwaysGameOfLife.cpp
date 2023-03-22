#include "ConwaysGameOfLife.hpp"
#include <ctime>
#include <random>
#include <vector>

void ConwaysGameOfLife::initialize_world(int rows, int cols) {
  srand(time(0));

  for (int i = 0; i < rows; ++i) {
    std::vector<int> curr_row;

    for (int j = 0; j < cols; ++j) {
      curr_row.push_back(rand() % 2); // push back 0 or 1
    }

    cells.push_back(curr_row);
  }
}

void ConwaysGameOfLife::next_generation() {
  size_t rows = cells.size();
  size_t cols = cells[0].size();

  // Get next generation cells
  int next_generation[rows][cols] = {0};
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      // Count nearbys
      int nearbys = 0;
      for (size_t row = i - 1; row <= i + 1; row++) {
        for (size_t col = j - 1; col <= j + 1; col++) {
          if (row >= 0
            && row < rows
            && col >= 0
            && col < cols
            && !(row == i && col == j) // [i][j] is itself
          ) {
            nearbys += cells[row][col];
          }
        }
      }
      // Conway's game of life rules:
      const int current = cells[i][j];
      if (current && nearbys < 2) {
        next_generation[i][j] = 0;
      } else if (current && (nearbys == 2 || nearbys == 3)) {
        next_generation[i][j] = current; // or: next_generation[i][j] = true;
      } else if (current && nearbys > 3) {
        next_generation[i][j] = 0;
      } else if (!current && nearbys == 3) {
        next_generation[i][j] = 1;
      }
    }
  }

  // Update
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cells[i][j] = next_generation[i][j];
    }
  }
}
