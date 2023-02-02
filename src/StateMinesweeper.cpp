#include <iostream> // TODO: remove

#include "StateMinesweeper.hpp"
#include "Renderer.hpp"
#include "TextureManager.hpp"
#include "MinesweeperCell.hpp"
#include "MinesweeperMark.hpp"
#include "CustomEvent.hpp"

bool StateMinesweeper::init() {
  SDL_Renderer* renderer = Renderer::get_renderer();

  // I do not know if loading the texture here is a good idea.
  return TextureManager::load(renderer, "res/minesweeper_sprites.png", "minesweeper_sprites");
}

void StateMinesweeper::handle_event(SDL_Event* e) {
  // Handle custom event first, because
  // CustomEvent::type() connot be case value.
  if (e->type == CustomEvent::type()) {
    switch (e->user.code) {
      case CUSTOMEVENT_MOUSE_CLICK:
        on_click(e);
        break;
      default:
        break;
    }

    return;
  }

  switch (e->type) {
    case SDL_KEYDOWN:
      {
        switch (e->key.keysym.sym) {
          default:
            break;
        }
      }
      break;
    case SDL_KEYUP:
      {
        switch (e->key.keysym.sym) {
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      {
        switch (e->button.button) {
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
        switch (e->button.button) {
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

void StateMinesweeper::update() {

}

void StateMinesweeper::draw() {
  SDL_Renderer* renderer = Renderer::get_renderer();

  // Draw map.

  const std::vector<std::vector<MinesweeperCell>> cells = map.get_cells();
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);

  for (int i = 0; i < map.get_rows(); i++) {
    for (int j = 0; j < map.get_cols(); j++) {
      SDL_Rect dstrect{ (int)j * 16, (int)i * 16, 16, 16 };
      MinesweeperCell cell = cells[i][j];
      cell.dig();
      SDL_Rect srcrect;

      if (cell.is_dug() && cell.is_mine()) { // draw mine
        srcrect = tiles["mine"];
      } else if (cell.is_dug()) { // draw number of around mines.
        srcrect = tiles["count_" + std::to_string(cell.around_mines_num())];
      } else if (cell.get_mark() == none) { // draw mark "none"
        srcrect = tiles["undug"];
      } else if (cell.get_mark() == certain) { // draw mark "certain"
        srcrect = tiles["mark_certain"];
      } else if (cell.get_mark() == uncertain) { // draw mark "uncertain"
        srcrect = tiles["mark_uncertain"];
      }

      TextureManager::draw(renderer, "minesweeper_sprites", &srcrect, &dstrect);
    }
  }
}

void StateMinesweeper::cleanup() {

}

void StateMinesweeper::on_click(SDL_Event* e) {
  SDL_MouseButtonEvent* down = static_cast<SDL_MouseButtonEvent*>(e->user.data1);
  SDL_MouseButtonEvent* up = static_cast<SDL_MouseButtonEvent*>(e->user.data2);

  if (!down || !up) {
    return;
  }

  std::cout << "TODO: on_click\n";
}
