#include <iostream>
#include <memory>

#include "Sprite.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "alias.hpp"
#include "engine.hpp"

void game() {
  auto sm = std::make_shared<StateMachine>();

  auto hwnd = engine::create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    300, 300, SDL_WINDOW_RESIZABLE);
  engine::set_window_icon(hwnd, "res/icon_16x16.bmp");

  auto hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  auto hfont = engine::open_font("res/SmileySans-Oblique.ttf", 16);
  auto text = engine::create_texture(hrdr, hfont, "Welcome to china! 你好，欢迎来到中国！", { 0, 0, 0, 255 }, 100);
  engine::close_font(hfont);
  Sprite msg{{ text }};
  msg.set_anchor_point(0.5, 0.5);

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
                msg.position.y -= 16;
                break;
              case SDLK_RIGHT:
                msg.position.x += 16;
                break;
              case SDLK_DOWN:
                msg.position.y += 16;
                break;
              case SDLK_LEFT:
                msg.position.x -= 16;
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
      msg.draw(hrdr, true);
    },

    .on_cleanup = [](StateMachine& sm) {
      std::cout << "menu cleanup();" << std::endl;
    }
  };

  auto world_state = std::make_unique<State>(sm, world_state_options);

  sm->push_state("world", std::move(world_state));
  sm->start(hrdr);
}

int main(int argc, char *args[]) {
  if (engine::init(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG)) {
    game();
  }
  engine::quit();

  return 0;
}
