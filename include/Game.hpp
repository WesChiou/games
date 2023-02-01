#ifndef _INCLUDE_GAME_HPP_
#define _INCLUDE_GAME_HPP_

#include <vector>
#include <string>

#include "State.hpp"

class Game {
public:
  void init(std::string title);
  void start();

  void push_state(State* state);
  void pop_state();

  void set_title(std::string title);
  void set_icon(std::string icon_path);

private:
  bool running{false};
  int real_time_fps{0};
  std::vector<State*> states;

  void handle_events();
  void update();
  void draw();
  void quit();
};

#endif
