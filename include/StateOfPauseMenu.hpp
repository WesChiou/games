#ifndef INCLUDE_STATEOFPAUSEMENU_HPP_
#define INCLUDE_STATEOFPAUSEMENU_HPP_

#include <memory>
#include "./alias.hpp"
#include "./TextureManager.hpp"
#include "./FontStyle.hpp"
#include "./State.hpp"

class StateOfPauseMenu : public State {
public:
  StateOfPauseMenu(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager);
  ~StateOfPauseMenu();
  void load();
  void handle_event(SDL_Event& event, StateManager& state_manager);
  void update();
  void render();
  void unload();

private:
  FontStyle alibabafont {
    .source = "res/AlibabaPuHuiTi/AlibabaPuHuiTi-3-55-Regular.ttf",
    .render_mode = FontRenderMode::Blended,
    .fg = { 255, 255, 255, 255 },
    .bg = { 25, 95, 125, 255 },
    .size = 16,
    // .outline = 1,
    // .align = TTF_WRAPPED_ALIGN_CENTER,
    // .style = TTF_STYLE_UNDERLINE,
    .wrap_length = 160,
  };
  SDL_Rect rect_continue_game{ 170, 170, 200, 30 };
  SDL_Rect rect_new_game{ 170, 170 + 50, 200, 30 };
  SDL_Rect rect_back_startmenu{ 170, 170 + 50 + 50, 200, 30 };
  HTEX continue_game_label;
  HTEX new_game_label;
  HTEX back_startmenu_label;
  HRDR hrdr;
  std::shared_ptr<TextureManager> texture_manager;
};

#endif  // INCLUDE_STATEOFPAUSEMENU_HPP_
