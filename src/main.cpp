// Copyright 2023 Qiu Weishi

#include <iostream>
#include <memory>
#include "../include/wish.hpp"
#include "State.hpp"

void game() {
  auto hwnd = engine::create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    400, 400, SDL_WINDOW_RESIZABLE);

  auto hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  auto o4 = std::make_shared<Object>(60, 60, 30, 30);
  o4->material = Material{{200, 200, 200, 255}};

  auto o3 = std::make_shared<Object>(10, 10, 60, 60);
  o3->material = Material{{120, 50, 250, 255}};
  o3->add(o4);

  auto o2 = std::make_shared<Object>(10, 10, 80, 80);
  o2->material = Material{{250, 50, 20, 255}};
  o2->add(o3);

  auto o1 = std::make_shared<Object>(10, 10, 100, 100);
  o1->material = Material{{120, 50, 20, 255}};
  o1->add(o2);

  Scene scene{hrdr};
  scene.add(o1);

  Rect camera{0, 0, 80, 80};
  Rect viewport{100, 100, 200, 200};
  auto sm = std::make_shared<StateMachine>();

  // Create menu

  StateOptions menu_options{
    .pause = true,
    .invisible = true,
    .sleep = true,
  };

  StateCallbacks menu_callbacks{
    .on_init = [](StateMachine& sm) {
      std::cout << "menu init();" << std::endl;
    },

    .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
    },

    .on_update = [](StateMachine& sm) {
    },

    .on_draw = [&](StateMachine& sm) {
    },

    .on_cleanup = [](StateMachine& sm) {
      std::cout << "menu cleanup();" << std::endl;
    }
  };

  auto menu_state = std::make_unique<State>(sm, menu_options, menu_callbacks);
  sm->push_state("menu", std::move(menu_state));

  // Create world

  StateOptions world_options{
    .pause = false,
    .invisible = false,
    .sleep = false,
  };

  StateCallbacks world_callbacks{
    .on_init = [](StateMachine& sm) {
      std::cout << "world init();" << std::endl;
    },

    .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
      if (event->type == SDL_USEREVENT) {
        if (event->user.code == static_cast<int>(
          engine::UserEventCode::mouse_click)) {
          std::cout << "clicked" << std::endl;
        }
        return;
      }

      switch (event->type) {
        case SDL_KEYDOWN:
          {
            switch (event->key.keysym.sym) {
              case SDLK_UP:
                camera.y -= 5;
                break;
              case SDLK_RIGHT:
                camera.x += 5;
                break;
              case SDLK_DOWN:
                camera.y += 5;
                break;
              case SDLK_LEFT:
                camera.x -= 5;
                break;
              default:
                break;
            }
          }
          break;
        case SDL_KEYUP:
          {
            switch (event->key.keysym.sym) {
              case SDLK_ESCAPE:
                std::cout << "show menu" << std::endl;
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

    .on_update = [&](StateMachine& sm) {
    },

    .on_draw = [&](StateMachine& sm) {
      // scene.update(nullptr, nullptr,   false);  // 000
      // scene.update(nullptr, nullptr,    true);  // 001
      // scene.update(nullptr, &viewport, false);  // 010
      // scene.update(nullptr, &viewport,  true);  // 011 *
      // scene.update(&camera, nullptr,   false);  // 100
      // scene.update(&camera, nullptr,    true);  // 101 *
      // scene.update(&camera, &viewport, false);  // 110
      scene.update(&camera, &viewport,  true);  // 111
    },

    .on_cleanup = [](StateMachine& sm) {
      std::cout << "world cleanup();" << std::endl;
    }
  };

  auto world_state = std::make_unique<State>(sm, world_options, world_callbacks);
  sm->push_state("world", std::move(world_state));

  // Start game loop
  sm->start(hrdr);
}

int main(int argc, char *args[]) {
  if (engine::init(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG)) {
    game();
  }
  engine::quit();

  return 0;
}
