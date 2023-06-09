#ifndef INCLUDE_CELLSMAP_HPP_
#define INCLUDE_CELLSMAP_HPP_

#include <vector>
#include <cstdint>
#include <ctime>

class CellsMap {
public:
  CellsMap(): rows(100), cols(100) {
    initialize_map(rows, cols);
  }

  CellsMap(int rows, int cols) {
    this->rows = (rows > 0 && rows <= 999) ? rows : 100;
    this->cols = (cols > 0 && cols <= 999) ? cols : 100;
    initialize_map(rows, cols);
  }

  const std::vector<std::vector<int>>& get_cells() const { return cells; }

  int get_rows() { return rows; }

  int get_cols() { return cols; }

  int get_generations() const { return generations; }

  int get_cells_count() {
    int count{ 0 };
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        count += cells[i][j];
      }
    }
    return count;
  }

  void next_generation() {
    // Get next generation cells
    int next_generation[rows][cols];
    std::fill(next_generation[0], next_generation[0] + rows * cols, 0);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        // Count nearbys
        int nearbys = 0;
        for (int row = i - 1; row <= i + 1; row++) {
          for (int col = j - 1; col <= j + 1; col++) {
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
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        cells[i][j] = next_generation[i][j];
      }
    }

    generations++;
  }

private:
  int rows{ 100 };
  int cols{ 100 };
  std::vector<std::vector<int>> cells;
  uint32_t generations{ 0 };

  void initialize_map(int rows, int cols) {
    srand(time(0));

    for (int i = 0; i < rows; ++i) {
      std::vector<int> curr_row;

      for (int j = 0; j < cols; ++j) {
        curr_row.push_back(rand() % 2); // push back 0 or 1
      }

      cells.push_back(curr_row);
    }
  }
};

#endif  // INCLUDE_CELLSMAP_HPP_
