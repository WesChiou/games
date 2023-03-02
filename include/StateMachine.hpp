#ifndef _INCLUDE_STATEMACHINE_HPP_
#define _INCLUDE_STATEMACHINE_HPP_

#include <vector>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "State.hpp"
#include "SDLEventHandler.hpp"
#include "alias.hpp"

class StateMachine {
public:
  StateMachine() {
    init();
  };

  // Start the game loop.
  void start(HRDR hrdr);

  // Push a state into game loop.
  void push_state(std::string name, std::unique_ptr<State> state);

  // Pop the last state.
  void pop_state();

  // Remove a state by its name.
  void remove_state(std::string name);

private:
  bool running{false};
  int real_time_fps{0};

  std::vector<std::pair<std::string, std::unique_ptr<State>>> states;

  std::vector<std::unique_ptr<SDLEventHandler>> event_handlers;

  void init();
  void handle_events();
  void update();
  void draw(HRDR hrdr);
  void quit();
};

#endif
