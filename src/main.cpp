#include <iostream>
#include <memory>

#include "Game.hpp"
#include "StateTest.hpp"

int main(int argc, char *args[]) {
  Game game{};

  WindowHandle hwnd = game.create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    300, 300, SDL_WINDOW_RESIZABLE);
  game.set_window_icon(hwnd, "res/icon_16x16.bmp");

  RendererHandle hrdr = game.create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  auto state_test = std::make_unique<StateTest>();
  game.push_state("test", std::move(state_test));

  game.start(hrdr);

  return 0;
}
