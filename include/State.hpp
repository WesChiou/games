#ifndef _INCLUDE_STATE_HPP_
#define _INCLUDE_STATE_HPP_

#include <SDL2/SDL.h>

class State {
public:
  virtual bool init() = 0;
  virtual void handle_event(SDL_Event* e) = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void cleanup() = 0;

  virtual ~State() = 0;

  bool is_pause() {
    return pause;
  };

  void toggle_pause(bool v) {
    pause = v;
  };

  bool is_invisible() {
    return invisible;
  };

  void toggle_invisible(bool v) {
    invisible = v;
  };

  bool is_sleep() {
    return sleep;
  };

  void toggle_sleep(bool v) {
    sleep = v;
  };

protected:
  bool pause{false}; // update or not
  bool invisible{false}; // draw or not
  bool sleep{false}; // handle_event or not
};

inline State::~State() {};

#endif
