#include "../include/utils.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace utils {
  bool is_square_number(int n) {
    return (n > -1) && (sqrt(n) == static_cast<int>(sqrt(n)));
  }

  int largest_multiple_of_n(int n, int upper_limit) {
    return upper_limit / n * n;
  }

  std::vector<int> surrounding_pieces(int z, int cols, int rows) {
    int x = z % cols;
    int y = std::floor(z / rows);

    int left  = x == 0        ? -1 : z - 1;
    int up    = y == 0        ? -1 : z - cols;
    int right = x == (cols - 1)  ? -1 : z + 1;
    int down  = y == (rows - 1)  ? -1 : z + cols;

    std::vector<int> pieces{left, up, right, down};
    pieces.erase(std::remove_if(pieces.begin(), pieces.end(),
      [](int i) { return i == -1; }), pieces.end());

    return pieces;
  }

  std::vector<int> shuffle_n_puzzle(std::vector<int> puzzle, int blank_code, int moves, int cols, int rows) {
    int blank = std::find(puzzle.begin(), puzzle.end(), blank_code) - puzzle.begin();

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < moves; ++i) {
      auto pieces = surrounding_pieces(blank, cols, rows);

      std::uniform_int_distribution<> dis(0, pieces.size() - 1);
      int pieceIndex = pieces[dis(g)];

      std::swap(puzzle[blank], puzzle[pieceIndex]);
      blank = pieceIndex;
    }

    return puzzle;
  }
}  // namespace utils
