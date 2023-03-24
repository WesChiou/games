#ifndef INCLUDE_STATE_HPP_
#define INCLUDE_STATE_HPP_

#include <SDL2/SDL.h>
#include <memory>
#include <functional>
#include "./alias.hpp"

class StateMachine;

using CommonFunc = std::function<void (StateMachine&)>;
using HandleEventFunc = std::function<void (StateMachine&, SDL_Event*)>;

struct StateCallbacks {
  CommonFunc on_init;
  HandleEventFunc on_handle_event;
  CommonFunc on_update;
  CommonFunc on_draw;
  CommonFunc on_cleanup;
};

struct StateOptions {
  bool pause{false};  // update or not
  bool invisible{false};  // draw or not
  bool sleep{false};  // handle_event or not
};

class State {
public:
  explicit State(std::weak_ptr<StateMachine> sm) : sm(sm) {}

  State(std::weak_ptr<StateMachine> sm, StateOptions options)
  : sm(sm), options(options) {}

  State(std::weak_ptr<StateMachine> sm, StateCallbacks callbacks)
  : sm(sm), callbacks(callbacks) {}

  State(std::weak_ptr<StateMachine> sm, StateOptions options, StateCallbacks callbacks)
  : sm(sm), options(options), callbacks(callbacks) {}

  void init() {
    auto sm_shared = sm.lock();
    if (callbacks.on_init && sm_shared) {
      callbacks.on_init(*sm_shared);
    }
  }

  void handle_event(SDL_Event* event) {
    if (options.sleep) return;
    auto sm_shared = sm.lock();
    if (callbacks.on_handle_event && sm_shared) {
      callbacks.on_handle_event(*sm_shared, event);
    }
  }

  void update() {
    if (options.pause) return;
    auto sm_shared = sm.lock();
    if (callbacks.on_update && sm_shared) {
      callbacks.on_update(*sm_shared);
    }
  }

  void draw() {
    if (options.invisible) return;
    auto sm_shared = sm.lock();
    if (callbacks.on_draw && sm_shared) {
      callbacks.on_draw(*sm_shared);
    }
  }

  void cleanup() {
    auto sm_shared = sm.lock();
    if (callbacks.on_cleanup && sm_shared) {
      callbacks.on_cleanup(*sm_shared);
    }
  }

  bool is_pause() { return options.pause; };
  bool is_invisible() { return options.invisible; };
  bool is_sleep() { return options.sleep; };

  void set_options(StateOptions options) {
    this->options = options;
  }

  void set_callbacks(StateCallbacks callbacks) {
    this->callbacks = callbacks;
  }

protected:
  std::weak_ptr<StateMachine> sm;
  StateOptions options;
  StateCallbacks callbacks;
};

#endif  // INCLUDE_STATE_HPP_
