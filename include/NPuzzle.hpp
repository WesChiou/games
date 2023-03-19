#ifndef _INCLUDE_NPUZZLE_HPP_
#define _INCLUDE_NPUZZLE_HPP_

#include <wish/wish.hpp>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>

enum class Direction {
  up, right, down, left
};

class NPuzzle {
public:
  NPuzzle(int n, TextureRegion image);

  void handle_event(SDL_Event* event);

  void update();

  void draw(SDL_Renderer *renderer);

  Rect image_region() {
    return image.get_region();
  };

private:
  int n{ 8 };
  int square_size{ 0 };
  TextureRegion image;
  std::vector<int> squares;
  std::map<int, Rect> split_regions;
  bool show_origin_image{ false };

  // is_pause is alias of show_origin_image.
  bool is_pause() { return show_origin_image; };
  // n-puzzle has (n + 1) squares.
  int total_squares() { return n + 1; };
  // (n + 1) is the last square, hide it.
  int hidden_number() { return n + 1; };
  // rows * rows = total_squares.
  int rows() { return std::sqrt(total_squares()); };
  // yes, cols is equal to rows.
  int cols() { return rows(); };

  void move_blank_square(Direction direction);
};

#endif
