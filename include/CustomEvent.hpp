#ifndef _INCLUDE_CUSTOMEVENT_HPP_
#define _INCLUDE_CUSTOMEVENT_HPP_

#include <stdexcept> // runtime_error

#include <SDL2/SDL.h>

#include "CustomEventCode.hpp"

class CustomEvent {
public:
  static bool init() {
    instance_impl();
    return true;
  };

  static CustomEvent& instance() {
    return instance_impl();
  };

  static void trigger(CustomEventCode code, void* data1);

  static void cleanup() {};

  static uint32_t type() {
    return CustomEvent::instance().event_type;
  };

  CustomEvent(CustomEvent const&) = delete;
  CustomEvent& operator = (CustomEvent const&) = delete;

private:
  uint32_t event_type;

  static CustomEvent& instance_impl() {
    static CustomEvent instance{};
    return instance;
  };

  CustomEvent() {
    event_type = SDL_RegisterEvents(1);
    if (event_type == ((Uint32) - 1)) {
      throw std::runtime_error{ "CustomEvent HAS FAILED TO CALL SDL_RegisterEvents()" };
    }
  };
};

#endif
