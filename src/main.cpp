#include <iostream>
#include <memory>

#include "Game.hpp"
#include "State.hpp"
#include "engine.hpp"

struct Line {
  Line(int row): row(row) {};
  int row{ 1 };
  double x{ 5.0 };
  void update() {
    x += 1;
  };
  void draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255);
    SDL_RenderDrawLine(renderer, 0, row, x, row);
  };
  void on_click() {
    x -= 5;
  };
};

int main(int argc, char *args[]) {
  if (!engine::init(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG)) {
    return 1;
  }

  Line line1(1);
  Line line2(21);

  auto game = std::make_shared<Game>();

  WindowHandle hwnd = game->create_window("Hello",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    300, 300, SDL_WINDOW_RESIZABLE);
  game->set_window_icon(hwnd, "res/icon_16x16.bmp");

  RendererHandle hrdr = game->create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  StateInitOptions menu_options{
    .on_init = [](Game& game) {
      std::cout << "menu init();" << std::endl;
    },
    .on_handle_event = [&line1, &line2](Game& game, SDL_Event* event) {
      if (event->type == SDL_USEREVENT
        && event->user.code == (int)engine::UserEventCode::mouse_click) {
        line1.on_click();
        line2.on_click();
      }
    },
    .on_update = [&line1, &line2](Game& game) {
      line1.update();
      line2.update();
    },
    .on_draw = [&line1, &line2](Game& game, SDL_Renderer *renderer) {
      line1.draw(renderer);
      line2.draw(renderer);
    },
    .on_cleanup = [](Game& game) {
      std::cout << "menu cleanup();" << std::endl;
    }
  };

  auto menu = std::make_unique<State>(game, menu_options);

  game->push_state("menu", std::move(menu));
  game->start(hrdr);

  engine::quit();

  return 0;
}
