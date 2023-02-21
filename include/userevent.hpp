#ifndef _INCLUDE_EVENT_HPP_
#define _INCLUDE_EVENT_HPP_

#include <cstdint>

#include <SDL2/SDL.h>

namespace userevent {
  enum class EventCode {
    mouse_click,
  };

  uint32_t register_userevent();
  uint32_t get_registered_type();
  void trigger(EventCode code, void* data1, void* data2);
}

#endif
