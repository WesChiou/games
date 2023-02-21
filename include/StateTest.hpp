#ifndef _INCLUDE_STATETEST_HPP_
#define _INCLUDE_STATETEST_HPP_

#include <iostream>

#include "State.hpp"

class StateTest: public State {
public:
  bool init() {
    std::cout << "StateTest init" << std::endl;
    return true;
  };
  void handle_event(SDL_Event* event);
  void update();
  void draw(RendererHandle hrdr);
  void cleanup() {
    std::cout << "StateTest cleanup" << std::endl;
  };
};

#endif
