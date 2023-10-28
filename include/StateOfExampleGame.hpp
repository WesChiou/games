#ifndef INCLUDE_STATEOFEXAMPLEGAME_HPP_
#define INCLUDE_STATEOFEXAMPLEGAME_HPP_

#include <memory>
#include "./alias.hpp"
#include "./TextureManager.hpp"
#include "./FontStyle.hpp"
#include "./ExampleGame.hpp"
#include "./State.hpp"

class StateOfExampleGame : public State {
public:
  StateOfExampleGame(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager);
  ~StateOfExampleGame();
  void load();
  void handle_event(SDL_Event& event, StateManager& state_manager);
  void update();
  void render();
  void unload();

private:
  ExampleGame game;
  bool pause{ false };
  FontStyle alibabafont {
    .source = "res/AlibabaPuHuiTi/AlibabaPuHuiTi-3-55-Regular.ttf",
    .render_mode = FontRenderMode::Blended,
    .fg = { 255, 255, 255, 255 },
    // .bg = { 25, 95, 125, 255 },
    .size = 36,
    // .outline = 1,
    // .align = TTF_WRAPPED_ALIGN_CENTER,
    // .style = TTF_STYLE_UNDERLINE,
    .wrap_length = 160,
  };
  HRDR hrdr;
  std::shared_ptr<TextureManager> texture_manager;
};

#endif  // INCLUDE_STATEOFEXAMPLEGAME_HPP_
