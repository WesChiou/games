#include <iostream>
#include <memory>

#include "StateMachine.hpp"
#include "State.hpp"
#include "handles.hpp"
#include "engine.hpp"

int main(int argc, char *args[]) {
  if (!engine::init(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG)) {
    return 1;
  }

  auto sm = std::make_shared<StateMachine>();

  auto hwnd = engine::create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    300, 300, SDL_WINDOW_RESIZABLE);
  engine::set_window_icon(hwnd, "res/icon_16x16.bmp");

  auto hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  auto image = engine::create_texture(hrdr, "res/icon_16x16.bmp");
  SDL_Rect srcrect{ 0, 0, 16, 16 };
  SDL_Rect dstrect{ 0, 0, 16, 16 };

  StateInitOptions world_state_options{
    .on_init = [](StateMachine& sm) {
      std::cout << "menu init();" << std::endl;
    },

    .on_handle_event = [](StateMachine& sm, SDL_Event* event) {
      if (event->type == SDL_USEREVENT
        && event->user.code == (int)engine::UserEventCode::mouse_click) {
        std::cout << "clicked" << std::endl;
      }
    },

    .on_update = [](StateMachine& sm) {

    },

    .on_draw = [&](StateMachine& sm, SDL_Renderer *renderer) {
      SDL_RenderCopy(renderer, image.get(), &srcrect, &dstrect);
    },

    .on_cleanup = [](StateMachine& sm) {
      std::cout << "menu cleanup();" << std::endl;
    }
  };

  auto world_state = std::make_unique<State>(sm, world_state_options);

  sm->push_state("world", std::move(world_state));
  sm->start(hrdr);

  engine::quit();

  return 0;
}
