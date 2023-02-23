#include <iostream>

#include "userevent.hpp"
#include "MouseClickEvent.hpp"

void MouseClickEvent::handle_event(SDL_Event *event) {
  if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
    handle_mouse_button_event(event->button);
  }
}

void MouseClickEvent::handle_mouse_button_event(SDL_MouseButtonEvent event) {
  switch (event.button) {
    case SDL_BUTTON_LEFT:
      {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
          left_down = std::make_unique<SDL_MouseButtonEvent>(event);
        } else if (event.type == SDL_MOUSEBUTTONUP && left_down) {
          userevent::trigger(userevent::EventCode::mouse_click
            , left_down.release()
            , new SDL_MouseButtonEvent(event));
          left_down.reset();
        }
      }
      break;
    case SDL_BUTTON_MIDDLE:
      {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
          middle_down = std::make_unique<SDL_MouseButtonEvent>(event);
        } else if (event.type == SDL_MOUSEBUTTONUP && middle_down) {
          userevent::trigger(userevent::EventCode::mouse_click
            , middle_down.release()
            , new SDL_MouseButtonEvent(event));
          middle_down.reset();
        }
      }
      break;
    case SDL_BUTTON_RIGHT:
      {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
          right_down = std::make_unique<SDL_MouseButtonEvent>(event);
        } else if (event.type == SDL_MOUSEBUTTONUP && right_down) {
          userevent::trigger(userevent::EventCode::mouse_click
            , right_down.release()
            , new SDL_MouseButtonEvent(event));
          right_down.reset();
        }
      }
      break;
    case SDL_BUTTON_X1:
      // TODO
      break;
    case SDL_BUTTON_X2:
      // TODO
      break;
    default:
      break;
  }
}
