#ifndef INCLUDE_SDLEVENTHANDLER_HPP_
#define INCLUDE_SDLEVENTHANDLER_HPP_

#include <SDL2/SDL.h>

class SDLEventHandler {
public:
  virtual ~SDLEventHandler() = default;
  virtual void handle_event(SDL_Event* event) = 0;
};

#endif  // INCLUDE_SDLEVENTHANDLER_HPP_
