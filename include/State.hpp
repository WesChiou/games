#ifndef _INCLUDE_STATE_HPP_
#define _INCLUDE_STATE_HPP_

#include <memory>
#include <functional>

#include <SDL2/SDL.h>

class StateMachine;

using CommonFunc = std::function<void (StateMachine&)>;
using HandleEventFunc = std::function<void (StateMachine&, SDL_Event*)>;
using DrawFunc = std::function<void (StateMachine&, SDL_Renderer*)>;

struct StateInitOptions {
  CommonFunc on_init;
  HandleEventFunc on_handle_event;
  CommonFunc on_update;
  DrawFunc on_draw;
  CommonFunc on_cleanup;
};

class State {
public:
  State(std::weak_ptr<StateMachine> sm) : sm(sm) {};
  State(std::weak_ptr<StateMachine> sm, StateInitOptions options)
  : on_init(options.on_init)
  , on_handle_event(options.on_handle_event)
  , on_update(options.on_update)
  , on_draw(options.on_draw)
  , on_cleanup(options.on_cleanup)
  , sm(sm) {};

  CommonFunc on_init;
  HandleEventFunc on_handle_event;
  CommonFunc on_update;
  DrawFunc on_draw;
  CommonFunc on_cleanup;

  virtual void init() {
    auto sm_shared = sm.lock();
    if (on_init && sm_shared) {
      on_init(*sm_shared);
    }
  };

  virtual void handle_event(SDL_Event* event) {
    auto sm_shared = sm.lock();
    if (on_handle_event && sm_shared) {
      on_handle_event(*sm_shared, event);
    }
  };

  virtual void update() {
    auto sm_shared = sm.lock();
    if (on_update && sm_shared) {
      on_update(*sm_shared);
    }
  };

  virtual void draw(std::shared_ptr<SDL_Renderer> hrdr) {
    auto sm_shared = sm.lock();
    if (on_draw && sm_shared) {
      on_draw(*sm_shared, hrdr.get());
    }
  };

  virtual void cleanup() {
    auto sm_shared = sm.lock();
    if (on_cleanup && sm_shared) {
      on_cleanup(*sm_shared);
    }
  };

  bool is_pause() { return pause; };
  void toggle_pause(bool v) { pause = v; };

  bool is_invisible() { return invisible; };
  void toggle_invisible(bool v) { invisible = v; };

  bool is_sleep() { return sleep; };
  void toggle_sleep(bool v) { sleep = v; };

protected:
  std::weak_ptr<StateMachine> sm;

  bool pause{false}; // update or not, using by StateMachine
  bool invisible{false}; // draw or not, using by StateMachine
  bool sleep{false}; // handle_event or not, using by StateMachine
};

#endif
