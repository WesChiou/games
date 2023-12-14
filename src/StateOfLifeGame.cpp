#include <iostream>
#include "../include/StateOfLifeGame.hpp"
#include "../include/StateOfLifeGameMenu.hpp"

StateOfLifeGame::StateOfLifeGame(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager)
: hrdr(hrdr), texture_manager(texture_manager) {
  std::cout << "StateOfLifeGame" << std::endl;
}

StateOfLifeGame::~StateOfLifeGame() {
  std::cout << "~StateOfLifeGame" << std::endl;
}

void StateOfLifeGame::load() {
  std::cout << "StateOfLifeGame load()" << std::endl;
}

void StateOfLifeGame::handle_event(SDL_Event& event, StateManager& state_manager) {
  switch (event.type) {
    case SDL_KEYDOWN:
      {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            {
              state_manager.edit_state("lifegame", {
                .should_handle_event = false,
                .should_update = false,
              });
              state_manager.add_state({
                .state = std::make_shared<StateOfLifeGameMenu>(hrdr, texture_manager),
                .unique_name = "lifegamemenu",
              });
            }
            break;
          case SDLK_TAB:
            {
              // Change speed_multiplier.
              switch (speed_multiplier) {
                case SpeedMultiplier::X1:
                  speed_multiplier = SpeedMultiplier::X4;
                  break;
                case SpeedMultiplier::X4:
                  speed_multiplier = SpeedMultiplier::X8;
                  break;
                case SpeedMultiplier::X8:
                  speed_multiplier = SpeedMultiplier::X1;
                  break;
                default:
                  speed_multiplier = SpeedMultiplier::X1;
                  break;
              }
            }
            break;
          case SDLK_SPACE:
            pause = !pause;
            break;
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEWHEEL:
      move_camera(0, 0, -(event.wheel.y));
      break;
    default:
      break;
  }
}

void StateOfLifeGame::update() {
  if (!pause) {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto time_span = duration_cast<duration<int, std::milli>>(now - last_update);
    if (time_span >= per_generation()) {
      life_game.next_generation();
      last_update = now;
    }
  }

  // Update camera
  const uint8_t* state = SDL_GetKeyboardState(nullptr);

  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
    move_camera(0, -20);
  }
  if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
    move_camera(20, 0);
  }
  if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
    move_camera(0, 20);
  }
  if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
    move_camera(-20, 0);
  }
}

void StateOfLifeGame::render() {
  draw_cells();
  draw_ui();
}

void StateOfLifeGame::unload() {
  std::cout << "StateOfLifeGame unload()" << std::endl;
}

SDL_Point StateOfLifeGame::get_mouse() {
  SDL_Point mouse{ 0, 0 };

  SDL_GetMouseState(&mouse.x, &mouse.y);

  mouse.x -= viewport.x;
  mouse.y -= viewport.y;

  float scale_x = static_cast<float>(viewport.w) / camera.w;
  float scale_y = static_cast<float>(viewport.h) / camera.h;
  mouse.x /= scale_x;
  mouse.y /= scale_y;

  return mouse;
}

void StateOfLifeGame::move_camera(int offset_x, int offset_y, int offset_z) {
  // Move camera on the x-axis
  camera.x += offset_x;
  if (camera.x < 0) {
    camera.x = 0;
  }
  if (camera.x + camera.w > get_map_width()) {
    camera.x = get_map_width() - camera.w;
  }

  // Move camera on the y-axis
  camera.y += offset_y;
  if (camera.y < 0) {
    camera.y = 0;
  }
  if (camera.y + camera.h > get_map_height()) {
    camera.y = get_map_height() - camera.h;
  }

  // Move camera on the z-axis (z-axis is a virtual axis, map it to camera.w and camera.h)
  if (offset_z != 0) {
    SDL_Point mouse_old = get_mouse();

    float zoom = 1 + 0.1 * offset_z;
    float new_w{ camera.w * zoom };
    float new_h{ camera.h * zoom };
    // TODO(weishi): No magic number.
    if (new_w < get_map_width()
      && new_w > cell_render_size * 10
      && new_h < get_map_height()
      && new_h > cell_render_size * 10) {
      camera.w = new_w;
      camera.h = new_h;
    }

    SDL_Point mouse_new = get_mouse();
    if (mouse_old.x > 0
      && mouse_old.x < viewport.w
      && mouse_new.x > 0
      && mouse_new.x < viewport.w) {
      move_camera(mouse_old.x - mouse_new.x, 0);
    }
    if (mouse_old.y > 0
      && mouse_old.y < viewport.h
      && mouse_new.y > 0
      && mouse_new.y < viewport.h) {
      move_camera(0, mouse_old.y - mouse_new.y);
    }
  }
}

void StateOfLifeGame::draw_ui() {
  SDL_RenderSetViewport(hrdr.get(), &viewport_ui);

  float scale_x = static_cast<float>(viewport_ui.w) / camera_ui.w;
  float scale_y = static_cast<float>(viewport_ui.h) / camera_ui.h;
  SDL_RenderSetScale(hrdr.get(), scale_x, scale_y);

  SDL_Rect clip_rect{ 0, 0, camera_ui.w, camera_ui.h };
  SDL_RenderSetClipRect(hrdr.get(), &clip_rect);

  SDL_Point offset{ -camera_ui.x, -camera_ui.y };

  auto op_t = texture_manager->get_texture_region(61);
  if (op_t.has_value()) {
    auto t = op_t.value();
    SDL_Rect dstrect{ 32, 32, 16, 16 };
    SDL_RenderCopy(hrdr.get(), t.htex.get(), &t.region, &dstrect);
  }

  // Reset renderer
  SDL_RenderSetScale(hrdr.get(), 1.0, 1.0);
  SDL_RenderSetClipRect(hrdr.get(), nullptr);
  SDL_RenderSetViewport(hrdr.get(), nullptr);
}

void StateOfLifeGame::draw_cells() {
  SDL_RenderSetViewport(hrdr.get(), &viewport);

  float scale_x = static_cast<float>(viewport.w) / camera.w;
  float scale_y = static_cast<float>(viewport.h) / camera.h;
  SDL_RenderSetScale(hrdr.get(), scale_x, scale_y);

  SDL_Rect clip_rect{ 0, 0, camera.w, camera.h };
  SDL_RenderSetClipRect(hrdr.get(), &clip_rect);

  SDL_Point offset{ -camera.x, -camera.y };
  auto cells = life_game.get_cells();

  for (int i = 0; i < life_game.get_rows(); i++) {
    for (int j = 0; j < life_game.get_cols(); j++) {
      SDL_Rect dstrect{
        .x = cell_render_size * j + 1 + offset.x,
        .y = cell_render_size * i + 1 + offset.y,
        .w = cell_render_size - 2,
        .h = cell_render_size - 2,
      };

      if (cells[i][j]) {  // Cell is alive
        SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 255);
      } else {  // Cell is dead
        SDL_SetRenderDrawColor(hrdr.get(), 240, 240, 240, 255);
      }

      SDL_RenderFillRect(hrdr.get(), &dstrect);
    }
  }

  // Reset renderer
  SDL_RenderSetScale(hrdr.get(), 1.0, 1.0);
  SDL_RenderSetClipRect(hrdr.get(), nullptr);
  SDL_RenderSetViewport(hrdr.get(), nullptr);
}
