#include <iostream>
#include <memory>

#include "Game.hpp"
#include "State.hpp"
#include "userevent.hpp"

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
    .on_handle_event = [&line1, &line2](SDL_Event* event) {
      if (event->type == SDL_USEREVENT
        && event->user.code == (int)userevent::EventCode::mouse_click) {
        line1.on_click();
        line2.on_click();
      }
    },
    .on_update = [&line1, &line2]() {
      line1.update();
      line2.update();
    },
    .on_draw = [&line1, &line2](SDL_Renderer *renderer) {
      line1.draw(renderer);
      line2.draw(renderer);
    },
  };

  auto menu = std::make_unique<State>(game, menu_options);

  game->push_state("menu", std::move(menu));
  game->start(hrdr);

  return 0;
}
