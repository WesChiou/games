#include <iostream> // TODO: remove
#include <string>

#include "MouseListener.hpp"
#include "CustomEvent.hpp"
#include "CustomEventCode.hpp"

void print_button(SDL_MouseButtonEvent e) {
  std::string e_type{};
  switch (e.type) {
    case SDL_MOUSEBUTTONDOWN:
      e_type = "SDL_MOUSEBUTTONDOWN";
      break;
    case SDL_MOUSEBUTTONUP:
      e_type = "SDL_MOUSEBUTTONUP";
      break;
    default:
      break;
  }
  std::cout << "type: " << e_type << "\n";

  std::string e_button{};
  switch (e.button) {
    case SDL_BUTTON_LEFT:
      e_button = "SDL_BUTTON_LEFT";
      break;
    case SDL_BUTTON_MIDDLE:
      e_button = "SDL_BUTTON_MIDDLE";
      break;
    case SDL_BUTTON_RIGHT:
      e_button = "SDL_BUTTON_RIGHT";
      break;
    case SDL_BUTTON_X1:
      e_button = "SDL_BUTTON_X1";
      break;
    case SDL_BUTTON_X2:
      e_button = "SDL_BUTTON_X2";
      break;
    default:
      break;
  }
  std::cout << "button: " << e_button << "\n";

  std::string e_state{};
  switch (e.state) {
    case SDL_PRESSED:
      e_state = "SDL_PRESSED";
      break;
    case SDL_RELEASED:
      e_state = "SDL_RELEASED";
      break;
    default:
      break;
  }
  std::cout << "state: " << e_state << "\n";

  std::cout << "x: " << e.x << "\n";

  std::cout << "y: " << e.y << "\n";

  std::cout << "clicks: " << static_cast<unsigned>(e.clicks) << "\n\n";
}

void MouseListener::on_listen() {
  std::stack<SDL_MouseButtonEvent>stack = MouseListener::instance().mouse_events;

  if (stack.empty()) {
    return;
  }

  SDL_MouseButtonEvent top = stack.top();

  // print_button(top);

  // Left mouse button released.
  if (top.button == SDL_BUTTON_LEFT && top.state == SDL_RELEASED) {
    SDL_MouseButtonEvent it;

    while (!stack.empty()) {
      it = stack.top();

      // Left mouse button pressed.
      if (it.button == SDL_BUTTON_LEFT && it.state == SDL_PRESSED) {
        SDL_Point* p1 = new SDL_Point{ it.x, it.y };
        SDL_Point* p2 = new SDL_Point{ top.x, top.y };
        CustomEvent::trigger(click, p1, p2);
        break;
      }

      stack.pop();
    }

    MouseListener::instance().mouse_events = {}; // clear stack
  }
}
