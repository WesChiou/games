#ifndef INCLUDE_STATE_HPP_
#define INCLUDE_STATE_HPP_

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>

class StateManager;

class State {
public:
  virtual ~State() = default;
  virtual void load() = 0;
  virtual void handle_event(SDL_Event& event, StateManager& state_manager) = 0;
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void unload() = 0;
};

struct StateNode {
  std::shared_ptr<State> state;
  std::string unique_name;
  bool should_handle_event{ true };
  bool should_update{ true };
  bool should_render{ true };
  bool need_to_fuse{ false };
};

struct StateConfig {
  bool should_handle_event{ true };
  bool should_update{ true };
  bool should_render{ true };
  bool need_to_fuse{ false };
};

class StateManager {
public:
  StateManager();
  ~StateManager();

  void handle_event(SDL_Event& event);
  void update();
  void render();

  void edit_state(std::string unique_name, StateConfig config);
  void add_state(StateNode node);

private:
  std::vector<StateNode> state_nodes;
};

#endif  // INCLUDE_STATE_HPP_
