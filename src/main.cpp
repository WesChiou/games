// Copyright 2023 Qiu Weishi

#include <iostream>
#include <memory>
#include "../include/Sprite.hpp"
#include "../include/Material.hpp"
#include "../include/Object.hpp"
#include "../include/Scene.hpp"
#include "../include/Camera.hpp"
#include "../include/Renderer.hpp"
#include "../include/State.hpp"
#include "../include/StateMachine.hpp"
#include "../include/alias.hpp"
#include "../include/engine.hpp"

void game() {
  auto sm = std::make_shared<StateMachine>();

  auto hwnd = engine::create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    300, 300, SDL_WINDOW_RESIZABLE);
  engine::set_window_icon(hwnd, "res/icon_16x16.bmp");

  auto hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  // auto hfont = engine::open_font("res/SmileySans-Oblique.ttf", 16);
  auto text = engine::create_texture(hrdr, "res/icon_16x16.bmp");
  TextureRegion text_region{text};
  Sprite msg{text_region};
  msg.set_anchor_point(0.5, 0.5);

  StateInitOptions world_state_options{
    .on_init = [](StateMachine& sm) {
      std::cout << "menu init();" << std::endl;
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

void game_no_statemachine() {
  auto hwnd = engine::create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    400, 400, SDL_WINDOW_RESIZABLE);
  engine::set_window_icon(hwnd, "res/icon_16x16.bmp");

  auto hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  auto o4 = std::make_unique<Object>(60, 60, 30, 30);
  o4->material = Material{{200, 200, 200, 255}};

  auto o3 = std::make_unique<Object>(10, 10, 60, 60);
  o3->material = Material{{120, 50, 250, 255}};
  o3->add(std::move(o4));

  auto o2 = std::make_unique<Object>(10, 10, 80, 80);
  o2->material = Material{{250, 50, 20, 255}};
  o2->add(std::move(o3));

  auto o1 = std::make_unique<Object>(10, 10, 100, 100);
  o1->material = Material{{120, 50, 20, 255}};
  o1->add(std::move(o2));

  Scene scene{};
  scene.add(std::move(o1));

  Camera camera{0, 0, 200, 200};
  Rect viewport{0, 0, 400, 400};
  Renderer renderer{hrdr};

  bool running = true;
  while (running) {
    SDL_Event event;
    SDL_StopTextInput();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        return;
      }

      switch (event.type) {
        case SDL_KEYDOWN:
          {
            switch (event.key.keysym.sym) {
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
        default:
          break;
      }
    }

    // update

    // Erase the last frame.
    SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 255);
    SDL_RenderClear(hrdr.get());
    // Draw
    renderer.render(scene, camera, &viewport);
    // Render the current frame.
    SDL_RenderPresent(hrdr.get());
  }
}

int main(int argc, char *args[]) {
  if (engine::init(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG)) {
    // game();
    game_no_statemachine();
  }
  engine::quit();

  return 0;
}
