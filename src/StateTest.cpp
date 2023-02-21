#include <iostream>

#include "StateTest.hpp"
#include "userevent.hpp"
#include "utils.hpp"

void StateTest::handle_event(SDL_Event* event) {
  if (event->type == SDL_USEREVENT) {
    switch (event->user.code) {
      case (int)userevent::EventCode::mouse_click:
        {
          auto down = static_cast<SDL_MouseButtonEvent*>(event->user.data1);
          auto up = static_cast<SDL_MouseButtonEvent*>(event->user.data2);
          std::cout << "click ----->\n";
          print(*down);
          print(*up);
          std::cout << "<===== click\n\n";
        }
        break;
      default:
        break;
    }

    return;
  }

  switch (event->type) {
    case SDL_KEYDOWN:
      {
        switch (event->key.keysym.sym) {
          default:
            break;
        }
      }
      break;
    case SDL_KEYUP:
      {
        switch (event->key.keysym.sym) {
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      {
        switch (event->button.button) {
          case SDL_BUTTON_LEFT:
            //
            break;
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEBUTTONUP:
      {
        switch (event->button.button) {
          case SDL_BUTTON_LEFT:
            //
            break;
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEMOTION:
      //
      break;
    default:
      break;
  }
}

void StateTest::update() {

}

void StateTest::draw(RendererHandle hrdr) {
  auto renderer = hrdr.get();

  SDL_Rect rect{ 10, 10, 100, 100 };
  SDL_SetRenderDrawColor(renderer, 255, 67, 23, 255);
  SDL_RenderDrawRect(renderer, &rect);
};
