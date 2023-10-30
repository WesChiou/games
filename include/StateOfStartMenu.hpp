#ifndef INCLUDE_STATEOFSTARTMENU_HPP_
#define INCLUDE_STATEOFSTARTMENU_HPP_

#include <SDL2/SDL.h>
#include <memory>
#include "./alias.hpp"
#include "./TextureManager.hpp"
#include "./FontStyle.hpp"
#include "./State.hpp"

class StateOfStartMenu : public State {
public:
  StateOfStartMenu(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager);
  ~StateOfStartMenu();
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
  SDL_Rect rect_examplegame{ 20, 20, 200, 50 };
  SDL_Rect rect_quit{ 20, 20 + 50 + 20, 200, 50 };
  HTEX label_examplegame;
  HTEX label_quit;
  HRDR hrdr;
  std::shared_ptr<TextureManager> texture_manager;
};

#endif  // INCLUDE_STATEOFSTARTMENU_HPP_
