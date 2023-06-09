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

const int CELL_SIZE = 10;
const int CAMERA_W = 800;
const int CAMERA_H = 640;
const int VIEWPORT_W = 800;
const int VIEWPORT_H = 640;

class GameMap {
public:
  GameMap() {
    cells_map = CellsMap();
  }

  GameMap(int rows, int cols) {
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
    for (int i = 0; i < cells_map.get_rows(); i++) {
      for (int j = 0; j < cells_map.get_cols(); j++) {
        Rect dstrect{
          .x = 10 * (int)j + 1 + offset.x,
          .y = 10 * (int)i + 1 + offset.y,
          .w = (int)CELL_SIZE - 2,
          .h = (int)CELL_SIZE - 2,
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

  void move_camera(int offset_x, int offset_y, int offset_z = 0) {
    // move camera x
    camera->x += offset_x;
    if (camera->x < 0) {
      camera->x = 0;
    }
    if (camera->x + camera->w > get_map_width()) {
      camera->x = get_map_width() - camera->w;
    }

    // move camera y
    camera->y += offset_y;
    if (camera->y < 0) {
      camera->y = 0;
    }
    if (camera->y + camera->h > get_map_height()) {
      camera->y = get_map_height() - camera->h;
    }

    // move camera z (z is a virtual property, map it to camera.w and camera.h)
    if (offset_z != 0) {
      Point mouse1 = get_mouse();

      float zoom = 1 + 0.1 * offset_z;
      float zoom_rate = (camera->w * zoom) / CAMERA_W;
      if (zoom_rate >= 0.5 && zoom_rate <= 2.0) {
        camera->w *= zoom;
        camera->h *= zoom;
      }

      Point mouse2 = get_mouse();
      if (mouse1.x > 0
        && mouse1.x < CAMERA_W
        && mouse2.x > 0
        && mouse2.x < CAMERA_W) {
        move_camera(mouse1.x - mouse2.x, 0);
      }
      if (mouse1.y > 0
        && mouse1.y < CAMERA_H
        && mouse2.y > 0
        && mouse2.y < CAMERA_H) {
        move_camera(0, mouse1.y - mouse2.y);
      }
    }
  }

  int get_map_width() {
    return CELL_SIZE * cells_map.get_cols();
  }

  int get_map_height() {
    return CELL_SIZE * cells_map.get_rows();
  }

  uint32_t per_generation() {
    return per_generation_x1 / (int)speed;
  }

  Point get_mouse() {
    Point mouse{ 0, 0 };

    SDL_GetMouseState(&mouse.x, &mouse.y);

    if (viewport) {
      mouse.x -= viewport->x;
      mouse.y -= viewport->y;
    }

    if (camera && viewport) {
      float scale_x = static_cast<float>(viewport->w) / camera->w;
      float scale_y = static_cast<float>(viewport->h) / camera->h;
      mouse.x /= scale_x;
      mouse.y /= scale_y;
    }

    return mouse;
  }

private:
  CellsMap cells_map;

  std::unique_ptr<Rect> camera = std::make_unique<Rect>(Rect{0, 0, CAMERA_W, CAMERA_H});
  std::unique_ptr<Rect> viewport = std::make_unique<Rect>(Rect{0, 0, VIEWPORT_W, VIEWPORT_H});

  bool pause{ false };
  uint32_t last_update{ 0 };
  uint32_t per_generation_x1{ 250 };
  Speed speed{ Speed::X1 };

  void set_speed(Speed new_speed) {
    speed = new_speed;
  }
};

#endif  // INCLUDE_GAMEMAP_HPP_
