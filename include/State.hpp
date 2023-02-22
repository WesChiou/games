#ifndef _INCLUDE_STATE_HPP_
#define _INCLUDE_STATE_HPP_

#include <memory>
#include <functional>

#include <SDL2/SDL.h>

#include "handles.hpp"

class Game;

using HandleEventFunc = std::function<void (SDL_Event*)>;
using UpdateFunc = std::function<void ()>;
using DrawFunc = std::function<void (SDL_Renderer*)>;

struct StateInitOptions {
  HandleEventFunc on_handle_event;
  UpdateFunc on_update;
  DrawFunc on_draw;
};

class State {
public:
  State(std::weak_ptr<Game> game) : game(game) {};
  State(std::weak_ptr<Game> game, StateInitOptions options)
  : on_handle_event(options.on_handle_event)
  , on_update(options.on_update)
  , on_draw(options.on_draw)
  , game(game) {};

  HandleEventFunc on_handle_event;
  UpdateFunc on_update;
  DrawFunc on_draw;

  virtual bool init() { return true; };
  virtual void handle_event(SDL_Event* event) {
    if (on_handle_event) on_handle_event(event);
  };
  virtual void update() {
    if (on_update) on_update();
  };
  virtual void draw(RendererHandle hrdr) {
    if (on_draw) on_draw(hrdr.get());
  };
  virtual void cleanup() {};

  bool is_pause() { return pause; };
  void toggle_pause(bool v) { pause = v; };

  bool is_invisible() { return invisible; };
  void toggle_invisible(bool v) { invisible = v; };

  bool is_sleep() { return sleep; };
  void toggle_sleep(bool v) { sleep = v; };

protected:
  std::weak_ptr<Game> game;

  bool pause{false}; // update or not, using by Game
  bool invisible{false}; // draw or not, using by Game
  bool sleep{false}; // handle_event or not, using by Game
};

#endif
