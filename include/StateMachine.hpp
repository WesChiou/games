#ifndef INCLUDE_STATEMACHINE_HPP_
#define INCLUDE_STATEMACHINE_HPP_

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include "./alias.hpp"
#include "./State.hpp"
#include "./SDLEventHandler.hpp"

class StateMachine {
public:
  StateMachine() {
    init();
  }

  // Start the game loop.
  void start(HRDR hrdr);

  // Push a state into game loop.
  void push_state(std::string name, std::shared_ptr<State> state);

  // Pop the last state.
  void pop_state();

  // Remove a state by its name.
  void remove_state(std::string name);

private:
  bool running{false};
  int real_time_fps{0};

  std::vector<std::pair<std::string, std::shared_ptr<State>>> states;

  std::vector<std::unique_ptr<SDLEventHandler>> event_handlers;

  void init();
  void handle_events();
  void update();
  void draw(HRDR hrdr);
  void quit();
};

#endif  // INCLUDE_STATEMACHINE_HPP_
