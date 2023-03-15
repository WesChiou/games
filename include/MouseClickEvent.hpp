#ifndef INCLUDE_MOUSECLICKEVENT_HPP_
#define INCLUDE_MOUSECLICKEVENT_HPP_

#include <memory>
#include "./SDLEventHandler.hpp"

class MouseClickEvent : public SDLEventHandler {
public:
  ~MouseClickEvent() {}
  void handle_event(SDL_Event *event) override;

private:
  std::unique_ptr<SDL_MouseButtonEvent> left_down;
  std::unique_ptr<SDL_MouseButtonEvent> middle_down;
  std::unique_ptr<SDL_MouseButtonEvent> right_down;

  void handle_mouse_button_event(SDL_MouseButtonEvent event);
};

#endif  // INCLUDE_MOUSECLICKEVENT_HPP_
