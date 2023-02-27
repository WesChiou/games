#ifndef _INCLUDE_STATE_HPP_
#define _INCLUDE_STATE_HPP_

#include <memory>
#include <functional>

#include <SDL2/SDL.h>

#include "handles.hpp"

class Game;

using CommonFunc = std::function<void (Game&)>;
using HandleEventFunc = std::function<void (Game&, SDL_Event*)>;
using DrawFunc = std::function<void (Game&, SDL_Renderer*)>;

struct StateInitOptions {
  CommonFunc on_init;
  HandleEventFunc on_handle_event;
  CommonFunc on_update;
  DrawFunc on_draw;
  CommonFunc on_cleanup;
};

class State {
public:
  State(std::weak_ptr<Game> game) : game(game) {};
  State(std::weak_ptr<Game> game, StateInitOptions options)
  : on_init(options.on_init)
  , on_handle_event(options.on_handle_event)
  , on_update(options.on_update)
  , on_draw(options.on_draw)
  , on_cleanup(options.on_cleanup)
  , game(game) {};

  CommonFunc on_init;
  HandleEventFunc on_handle_event;
  CommonFunc on_update;
  DrawFunc on_draw;
  CommonFunc on_cleanup;

  virtual void init() {
    auto shared_game = game.lock();
    if (on_init && shared_game) {
      on_init(*shared_game);
    }
  };

  virtual void handle_event(SDL_Event* event) {
    auto shared_game = game.lock();
    if (on_handle_event && shared_game) {
      on_handle_event(*shared_game, event);
    }
  };

  virtual void update() {
    auto shared_game = game.lock();
    if (on_update && shared_game) {
      on_update(*shared_game);
    }
  };

  virtual void draw(RendererHandle hrdr) {
    auto shared_game = game.lock();
    if (on_draw && shared_game) {
      on_draw(*shared_game, hrdr.get());
    }
  };

  virtual void cleanup() {
    auto shared_game = game.lock();
    if (on_cleanup && shared_game) {
      on_cleanup(*shared_game);
    }
  };

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
