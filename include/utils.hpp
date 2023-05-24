#ifndef INCLUDE_UTILS_HPP_
#define INCLUDE_UTILS_HPP_

#include <vector>

namespace utils {
  // If n is a square number. 4, 9, 16, etc.
  bool is_square_number(int n);

  // Find the largest possible integer with a given upper limit,
  // which must be a multiple of n.
  int largest_multiple_of_n(int n, int upper_limit);

  // Find surrounding pieces when we treat a
  // one-dimensional array as a two-dimensional matrix
  std::vector<int> surrounding_pieces(int z, int cols, int rows);

  // n-puzzle shuffler
  std::vector<int> shuffle_n_puzzle(std::vector<int> puzzle, int blank_code, int moves, int cols, int rows);
}  // namespace utils

#endif  // INCLUDE_UTILS_HPP_
