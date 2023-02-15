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
  void handle_event(SDL_Event* e) {};
  void update() {};
  void draw(RendererHandle hrdr) {
    auto renderer = hrdr.get();

    SDL_Rect rect{ 10, 10, 100, 100 };
    SDL_SetRenderDrawColor(renderer, 255, 67, 23, 255);
    SDL_RenderDrawRect(renderer, &rect);
  };
  void cleanup() {
    std::cout << "StateTest cleanup" << std::endl;
  };
};

#endif
