#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "utils.hpp"
#include "NPuzzle.hpp"

NPuzzle::NPuzzle(int n, TextureRegion image) {
  this->n = utils::is_square_number(n + 1) ? n : 8;

  // Cut image to be:
  // 1. A square image (width is equal to height);
  // 2. Image size is an integer multiple of a single square size.
  int image_size = utils::largest_multiple_of_n(rows(), std::min(image.get_w(), image.get_h()));

  if (!image_size || !image.get_texture()) {
    throw std::runtime_error("Image size is too small.");
  };

  this->image = image;
  this->image.set_region({ 0, 0, image_size, image_size });

  // Initialize squares and split_regions
  square_size = image_size / rows();
  for (int r = 0; r < rows(); r++) {
    for (int c = 0; c < cols(); c++) {
      int i = r * rows() + c + 1;
      squares.push_back(i);
      split_regions[i] = {
        .x = square_size * c,
        .y = square_size * r,
        .w = square_size,
        .h = square_size,
      };
    }
  }

  // shuffle squares
  // std::random_shuffle(squares.begin(), squares.end()); // can't insure solvable

  squares = utils::shuffle_n_puzzle(squares, hidden_number(), n * 100, cols(), rows());
  // for (auto i : test) std::cout << i << " ";
};

void NPuzzle::handle_event(SDL_Event* event) {
  if (is_pause()) return;

  if (event->type == SDL_USEREVENT) {
    if (event->user.code == (int)engine::UserEventCode::mouse_click) {
      std::cout << "clicked image" << std::endl;
    }
    return;
  }

  switch (event->type) {
    case SDL_KEYDOWN:
      {
        switch (event->key.keysym.sym) {
          case SDLK_UP:
            move_blank_square(Direction::down);
            break;
          case SDLK_RIGHT:
            move_blank_square(Direction::left);
            break;
          case SDLK_DOWN:
            move_blank_square(Direction::up);
            break;
          case SDLK_LEFT:
            move_blank_square(Direction::right);
            break;
          default:
            break;
        }
      }
      break;
    default:
      break;
  }

};

void NPuzzle::update() {
  const uint8_t* state = SDL_GetKeyboardState(nullptr);
  show_origin_image = (state[SDL_SCANCODE_LALT] || state[SDL_SCANCODE_RALT]);
};

void NPuzzle::draw(SDL_Renderer *renderer) {
  if (show_origin_image) {
    SDL_RenderCopy(renderer, image.get_texture(), &image.get_region(), &image.get_region());
    return;
  }

  for (int r = 0; r < rows(); r++) {
    for (int c = 0; c < cols(); c++) {
      Rect dstrect = {
        .x = square_size * c,
        .y = square_size * r,
        .w = square_size,
        .h = square_size,
      };
      int i = r * rows() + c;
      int ii = squares[i];

      if (ii == hidden_number()) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &dstrect);
      } else {
        auto curr = split_regions[ii];
        SDL_RenderCopy(renderer, image.get_texture(), &curr, &dstrect);
      }
    }
  }
};

void NPuzzle::move_blank_square(Direction direction) {
  int curr = std::find(squares.begin(), squares.end(), hidden_number()) - squares.begin();
  int x = curr % cols();
  int y = std::floor(curr / rows());
  Point from{ x, y };
  Point to{ -1, -1 };

  switch (direction) {
    case Direction::up:
      to = { .x = from.x, .y = from.y - 1 };
      break;
    case Direction::right:
      to = { .x = from.x + 1, .y = from.y };
      break;
    case Direction::down:
      to = { .x = from.x, .y = from.y + 1 };
      break;
    case Direction::left:
      to = { .x = from.x - 1, .y = from.y };
      break;
    default:
      break;
  }

  if (to.x < 0 || to.x >= cols() || to.y < 0 || to.y >= rows()) {
    return;
  }

  int target = to.y * rows() + to.x;
  std::swap(squares[curr], squares[target]);
};
