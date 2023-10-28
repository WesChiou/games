#include <SDL2/SDL.h>
#include <cstdint>
#include <string>
#include <stdexcept>
#include "../include/userevent.hpp"

namespace userevent {
  uint32_t get_type() {
    static uint32_t type = SDL_RegisterEvents(1);
    if (type == (uint32_t) - 1) {
      throw std::runtime_error("SDL_RegisterEvents Has Failed: " + std::string(SDL_GetError()));
    }
    return type;
  }

  void trigger(Code code, void* data1, void* data2) {
    SDL_Event event;
    SDL_zero(event);
    event.type = get_type();
    event.user.code = static_cast<int>(code);
    event.user.data1 = data1;
    event.user.data2 = data2;

    SDL_PushEvent(&event);
  }
}  // namespace userevent
