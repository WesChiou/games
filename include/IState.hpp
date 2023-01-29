#ifndef _INCLUDE_ISTATE_HPP_
#define _INCLUDE_ISTATE_HPP_

#include <SDL2/SDL.h>

class IState {
public:
  virtual bool init() = 0;
  virtual void handle_event(SDL_Event* e) = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void cleanup() = 0;

  virtual ~IState() = 0;

  bool pause{false}; // update or not
  bool invisible{false}; // draw or not
  bool sleep{false}; // handle_event or not
};

inline IState::~IState() {};

#endif
