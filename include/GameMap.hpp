#ifndef INCLUDE_GAMEMAP_HPP_
#define INCLUDE_GAMEMAP_HPP_

#include <corecrt.h>
#include <cstdint>
#include <wish/wish.hpp>
#include "CellsMap.hpp"

enum class Speed {
  X1 = 1,
  X4 = 4,
  X8 = 8,
};

class GameMap {
public:
  GameMap() {
    cells_map = CellsMap(rows, cols);
  }

  GameMap(int rows, int cols): rows(rows), cols(cols) {
    cells_map = CellsMap(rows, cols);
  }

  void draw_cells(HRDR hrdr) {
    SDL_Renderer* renderer = hrdr.get();

    if (!renderer) return;

    // set render viewport
    if (viewport) {
      SDL_RenderSetViewport(renderer, viewport.get());
    }

    // set render scale
    if (camera && viewport) {
      float scale_x = static_cast<float>(viewport->w) / camera->w;
      float scale_y = static_cast<float>(viewport->h) / camera->h;

      SDL_RenderSetScale(renderer, scale_x, scale_y);
    }

    // set render camera
    Point offset{ 0, 0 };

    if (camera) {
      offset.x = -camera->x;
      offset.y = -camera->y;

      Rect clip_rect{ 0, 0, camera->w, camera->h };
      SDL_RenderSetClipRect(renderer, &clip_rect);
    }

    // draw cells
    auto cells = cells_map.get_cells();
    size_t rows = cells.size();
    size_t cols = cells.size() >= 1 ? cells[0].size() : 0;

    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        Rect dstrect{
          .x = 10 * (int)j + 1 + offset.x,
          .y = 10 * (int)i + 1 + offset.y,
          .w = (int)cell_size - 2,
          .h = (int)cell_size - 2,
        };

        if (cells[i][j]) { // cell is alive
          SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 255);
        } else { // cell is dead
          SDL_SetRenderDrawColor(hrdr.get(), 240, 240, 240, 255);
        }
        SDL_RenderFillRect(hrdr.get(), &dstrect);
      }
    }

    // Reset renderer
    SDL_RenderSetScale(renderer, 1.0, 1.0);
    SDL_RenderSetClipRect(renderer, nullptr);
    SDL_RenderSetViewport(renderer, nullptr);
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
    // move camera
    const uint8_t* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_UP]) {
      move_camera(0, -20);
    }
    if (state[SDL_SCANCODE_RIGHT]) {
      move_camera(20, 0);
    }
    if (state[SDL_SCANCODE_DOWN]) {
      move_camera(0, 20);
    }
    if (state[SDL_SCANCODE_LEFT]) {
      move_camera(-20, 0);
    }

    if (!pause) {
      uint32_t current = SDL_GetTicks();
      uint32_t dt = current - last_update;
      if (dt >= per_generation()) {
        cells_map.next_generation();
        last_update = current;
      }
    }
  }

  void move_camera(int offset_x, int offset_y) {
    camera->x += offset_x;
    if (camera->x < 0) {
      camera->x = 0;
    }
    if (camera->x + camera->w > get_map_width()) {
      camera->x = get_map_width() - camera->w;
    }

    camera->y += offset_y;
    if (camera->y < 0) {
      camera->y = 0;
    }
    if (camera->y + camera->h > get_map_height()) {
      camera->y = get_map_height() - camera->h;
    }
  }

  int get_map_width() {
    return cell_size * cols;
  }

  int get_map_height() {
    return cell_size * rows;
  }

  uint32_t per_generation() {
    return per_generation_x1 / (int)speed;
  }

private:
  uint32_t rows{ 100 };
  uint32_t cols{ 100 };
  uint32_t cell_size{ 10 };
  CellsMap cells_map;

  std::unique_ptr<Rect> camera = std::make_unique<Rect>(Rect{0, 0, 800, 640});
  std::unique_ptr<Rect> viewport = std::make_unique<Rect>(Rect{0, 0, 800, 640});

  bool pause{ false };
  uint32_t last_update{ 0 };
  uint32_t per_generation_x1{ 250 };
  Speed speed{ Speed::X1 };

  void set_speed(Speed new_speed) {
    speed = new_speed;
  }
};

#endif  // INCLUDE_GAMEMAP_HPP_
