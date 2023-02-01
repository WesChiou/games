#ifndef _INCLUDE_STATEMINESWEEPER_HPP_
#define _INCLUDE_STATEMINESWEEPER_HPP_

#include "State.hpp"
#include "MinesweeperMap.hpp"

class StateMinesweeper: public State {
public:
  bool init();
  void handle_event(SDL_Event* e);
  void update();
  void draw();
  void cleanup();

private:
  MinesweeperMap map{9, 12, 10};
};

#endif
