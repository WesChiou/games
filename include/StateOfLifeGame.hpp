#ifndef INCLUDE_STATEOFLIFEGAME_HPP_
#define INCLUDE_STATEOFLIFEGAME_HPP_

#include <memory>
#include <chrono>
#include <ratio>
#include "./alias.hpp"
#include "./TextureManager.hpp"
#include "./FontStyle.hpp"
#include "./LifeGame.hpp"
#include "./State.hpp"

enum class SpeedMultiplier {
  X1 = 1,
  X4 = 4,
  X8 = 8,
};

class StateOfLifeGame : public State {
public:
  StateOfLifeGame(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager);
  ~StateOfLifeGame();
  void load();
  void handle_event(SDL_Event& event, StateManager& state_manager);
  void update();
  void render();
  void unload();

private:
  LifeGame life_game;
  bool pause{ false };
  SDL_Rect camera{ 0, 0, 800, 640 };
  SDL_Rect viewport{ 0, 0, 800, 640 };
  SDL_Rect camera_ui{ 0, 0, 800, 640 };
  SDL_Rect viewport_ui{ 0, 0, 800, 640 };
  int cell_render_size{ 10 };
  const std::chrono::duration<int, std::milli> default_per_generation{ 250 };
  SpeedMultiplier speed_multiplier{ SpeedMultiplier::X1 };
  std::chrono::steady_clock::time_point last_update{ std::chrono::steady_clock::now() };
  HRDR hrdr;
  std::shared_ptr<TextureManager> texture_manager;

  std::chrono::duration<int, std::milli> per_generation() {
    return default_per_generation / static_cast<int>(speed_multiplier);
  }

  int get_map_width() {
    return cell_render_size * life_game.get_cols();
  }

  int get_map_height() {
    return cell_render_size * life_game.get_rows();
  }

  SDL_Point get_mouse();
  void move_camera(int offset_x, int offset_y, int offset_z = 0);
  void draw_ui();
  void draw_cells();
};

#endif  // INCLUDE_STATEOFLIFEGAME_HPP_
