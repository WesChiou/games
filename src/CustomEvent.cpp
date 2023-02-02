#include "CustomEvent.hpp"
#include "CustomEventCode.hpp"

void CustomEvent::trigger(CustomEventCode code, void* data1, void* data2) {
  SDL_Event event;

  event.type = CustomEvent::instance().event_type;
  event.user.code = code;
  event.user.data1 = data1;
  event.user.data2 = data2;

  SDL_PushEvent(&event);
}
