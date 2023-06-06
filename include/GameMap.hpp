#ifndef INCLUDE_GAMEMAP_HPP_
#define INCLUDE_GAMEMAP_HPP_

#include <corecrt.h>
#include <cstdint>
#include <wish/wish.hpp>
#include "CellsMap.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"

enum class Speed {
  X1 = 1,
  X4 = 4,
  X8 = 8,
};

class GameMap {
public:
  GameMap() {
    cells_map = CellsMap();
  }

  GameMap(int rows, int cols) {
    cells_map = CellsMap(rows, cols);
  }

  void draw_cells(HRDR hrdr) {
    auto cells = cells_map.get_cells();
    size_t rows = cells.size();
    size_t cols = cells.size() >= 1 ? cells[0].size() : 0;

    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        Rect dstrect{ 10 * (int)j + 1, 10 * (int)i + 1, 8, 8 };
        if (cells[i][j]) {
          SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 255);
        } else {
          SDL_SetRenderDrawColor(hrdr.get(), 255, 255, 255, 255);
        }
        SDL_RenderFillRect(hrdr.get(), &dstrect);
      }
    }
  }

  void speed_up() {
    switch (speed) {
    case Speed::X1:
      set_speed(Speed::X4);
      break;
    case Speed::X4:
      set_speed(Speed::X8);
      break;
    case Speed::X8:
      set_speed(Speed::X1);
      break;
    }
  }

  void toggle_pause() {
    pause = !pause;
  }

  void update() {
    uint32_t current = SDL_GetTicks();
    uint32_t dt = current - last_update;
    if (dt >= per_generation()) {
      cells_map.next_generation();
      last_update = current;
    }
  }

  uint32_t per_generation() {
    return per_generation_x1 / (int)speed;
  }

private:
  CellsMap cells_map;

  bool pause{ false };
  uint32_t last_update{ 0 };
  uint32_t per_generation_x1{ 250 };
  Speed speed{ Speed::X1 };

  void set_speed(Speed new_speed) {
    speed = new_speed;
  }
};

#endif  // INCLUDE_GAMEMAP_HPP_
