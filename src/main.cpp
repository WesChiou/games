// Copyright 2023 Qiu Weishi

#include <iostream>
#include <memory>
#include <wish/wish.hpp>
#include "../include/NPuzzle.hpp"

void game() {
  auto sm = std::make_shared<StateMachine>();

  auto hwnd = engine::create_window("缺一块 (N-Puzzle)",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    300, 300, 0);
  engine::set_window_icon(hwnd, "res/icon_32x32.png");

  auto hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  auto htex = engine::create_texture(hrdr, "res/npuzzle_test.jpg");
  TextureRegion tr{ htex };
  NPuzzle npuzzle{ 15, tr };
  engine::set_window_size(hwnd, npuzzle.image_region().w, npuzzle.image_region().h);

  StateCallbacks state_callbacks{
    .on_init = [](StateMachine& sm) {
    },

    .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
      npuzzle.handle_event(event);
    },

    .on_update = [&](StateMachine& sm) {
      npuzzle.update();
    },

    .on_draw = [&](StateMachine& sm) {
      npuzzle.draw(hrdr.get());
    },

    .on_cleanup = [](StateMachine& sm) {
    }
  };

  auto world_state = std::make_unique<State>(sm, state_callbacks);

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
