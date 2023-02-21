#include <iostream>

#include "userevent.hpp"

namespace userevent {
  uint32_t register_userevent() {
    uint32_t type = SDL_RegisterEvents(1);
    if (type == (uint32_t) - 1) {
      std::cerr << "SDL_RegisterEvents has failed: " << SDL_GetError() << std::endl;
    }
    return type;
  };

  uint32_t get_userevent_type() {
    static uint32_t type = register_userevent();
    return type;
  };

  void trigger(EventCode code, void* data1, void* data2) {
    SDL_Event event;
    SDL_zero(event);
    event.type = get_userevent_type();
    event.user.code = (int)code;
    event.user.data1 = data1;
    event.user.data2 = data2;

    SDL_PushEvent(&event);
  };
}
