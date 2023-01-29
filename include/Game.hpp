#ifndef _INCLUDE_GAME_HPP_
#define _INCLUDE_GAME_HPP_

#include <vector>
#include <string>

#include <SDL2/SDL_ttf.h>

#include "IState.hpp"

class Game {
public:
  void init(std::string title);
  void start();

  void push_state(IState* state);
  void pop_state();

private:
  bool running{false};
  int real_time_fps{0};
  std::vector<IState*> states;

  void handle_events();
  void update();
  void draw();
  void quit();
};

#endif
