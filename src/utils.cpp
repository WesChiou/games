#include "utils.hpp"

void print(SDL_MouseButtonEvent e) {
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
