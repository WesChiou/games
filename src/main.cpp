#include <iostream>
#include <memory>

#include "Sprite.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "alias.hpp"
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

  auto test_htex = engine::create_texture(hrdr, "res/Minesweepertiles-windows3.1mexpwep.png");

  Sprite test_sprite{{ test_htex, { 0, 0, 16, 32 } }};

  StateInitOptions world_state_options{
    .on_init = [](StateMachine& sm) {
      std::cout << "menu init();" << std::endl;
    },

    .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
      if (event->type == SDL_USEREVENT) {
        if (event->user.code == (int)engine::UserEventCode::mouse_click) {
          std::cout << "clicked" << std::endl;
        }
        return;
      }

      switch (event->type) {
        case SDL_KEYDOWN:
          {
            switch (event->key.keysym.sym) {
              case SDLK_UP:
                test_sprite.position.y -= 16;
                break;
              case SDLK_RIGHT:
                test_sprite.position.x += 16;
                break;
              case SDLK_DOWN:
                test_sprite.position.y += 16;
                break;
              case SDLK_LEFT:
                test_sprite.position.x -= 16;
                break;
              default:
                break;
            }
          }
          break;
        default:
          break;
      }
    },

    .on_update = [](StateMachine& sm) {

    },

    .on_draw = [&](StateMachine& sm, SDL_Renderer *renderer) {
      test_sprite.draw(hrdr, true);
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
