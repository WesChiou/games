#include <iostream> // TODO: remove

#include "StateMinesweeper.hpp"
#include "Renderer.hpp"
#include "TextureManager.hpp"
#include "MinesweeperCell.hpp"
#include "MinesweeperMark.hpp"
#include "CustomEvent.hpp"

bool StateMinesweeper::init() {
  SDL_Renderer* renderer = Renderer::get_renderer();

  int face_size = 30;
  int header_h = 50;
  int map_w = map.get_cols() * 16;
  int map_h = map.get_rows() * 16;

  auto obj_header = GameObject{ 0, 0, header_h, map_w };
  obj_header.add_event_listener(click, [](SDL_Event* event) {
    std::cout << "click obj_header\n";
  });

  auto obj_face = GameObject{ (map_w - face_size) / 2, (header_h - face_size) / 2, face_size, face_size };
  obj_face.add_event_listener(click, [](SDL_Event* event) {
    std::cout << "click obj_face\n";
  });

  auto obj_map = GameObject{ 0, header_h, map_h, map_w };
  obj_map.add_event_listener(click, [](SDL_Event* event) {
    std::cout << "click obj_map\n";
  });

  objects.push_back(obj_header);
  objects.push_back(obj_face);
  objects.push_back(obj_map);

  // I do not know if loading the texture here is a good idea.
  return TextureManager::load(renderer, "res/minesweeper_sprites.png", "minesweeper_sprites");
}

void StateMinesweeper::handle_event(SDL_Event* e) {
  // Handle custom event first, because
  // CustomEvent::type() connot be case value.
  if (e->type == CustomEvent::type()) {
    switch (e->user.code) {
      case click:
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

  // Draw objects border
  {
    SDL_SetRenderDrawColor(renderer, 88, 88, 88, 255);
    for (auto object : objects) {
      SDL_Rect rect{ object.x, object.y, object.width, object.height };
      SDL_RenderDrawRect(renderer, &rect);
    }
  }

  // Draw map.
  {
    const std::vector<std::vector<MinesweeperCell>> cells = map.get_cells();
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);

    for (int i = 0; i < map.get_rows(); i++) {
      for (int j = 0; j < map.get_cols(); j++) {
        SDL_Rect dstrect{ j * 16, i * 16, 16, 16 };
        MinesweeperCell cell = cells[i][j];
        cell.dig();
        SDL_Rect srcrect;

        if (cell.is_dug() && cell.is_mine()) { // draw mine
          srcrect = imgs["mine"];
        } else if (cell.is_dug()) { // draw number of around mines.
          srcrect = imgs["count_" + std::to_string(cell.around_mines_num())];
        } else if (cell.get_mark() == none) { // draw mark "none"
          srcrect = imgs["undug"];
        } else if (cell.get_mark() == certain) { // draw mark "certain"
          srcrect = imgs["mark_certain"];
        } else if (cell.get_mark() == uncertain) { // draw mark "uncertain"
          srcrect = imgs["mark_uncertain"];
        }

        TextureManager::draw(renderer, "minesweeper_sprites", &srcrect, &dstrect);
      }
    }
  }
}

void StateMinesweeper::cleanup() {

}

void StateMinesweeper::on_click(SDL_Event* e) {
  SDL_Point* down = static_cast<SDL_Point*>(e->user.data1);
  SDL_Point* up = static_cast<SDL_Point*>(e->user.data2);

  if (!down || !up) {
    return;
  }

  for (auto object : objects) {
    SDL_Rect rect{ object.x, object.y, object.width, object.height };
    if (SDL_PointInRect(down, &rect) && SDL_PointInRect(up, &rect)) {
      object.dispatch_event(e);
    }
  }
}
