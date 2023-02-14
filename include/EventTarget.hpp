#ifndef _INCLUDE_EVENTTARGET_HPP_
#define _INCLUDE_EVENTTARGET_HPP_

#include <map>
#include <stdint.h>
#include <functional>
#include <algorithm>

#include <SDL2/SDL.h>

#include "CustomEventCode.hpp"

using EventListener = std::function<void(SDL_Event*)>;

class EventTarget {
public:
  void add_event_listener(CustomEventCode code, EventListener listener) {
    listeners[code] = listener;
  };

  void remove_event_listener(CustomEventCode code) {
    listeners.erase(code);
  };

  void dispatch_event(SDL_Event* event) {
    auto it = listeners.find((CustomEventCode)event->user.code);
    if (it == listeners.end()) {
      return;
    }
    auto& listener = it->second;
    listener(event);
  };

private:
  std::map<CustomEventCode, EventListener> listeners;
};

#endif
