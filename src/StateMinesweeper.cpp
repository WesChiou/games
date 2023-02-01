#include "StateMinesweeper.hpp"
#include "RendererManager.hpp"
#include "TextureManager.hpp"
#include "MinesweeperCell.hpp"
#include "MinesweeperMark.hpp"

bool StateMinesweeper::init() {
  SDL_Renderer* renderer = RendererManager::get_renderer();

  // I do not know if loading the texture here is a good idea.
  return TextureManager::load(renderer, "res/minesweeper_sprites.png", "minesweeper_sprites");
}

void StateMinesweeper::handle_event(SDL_Event* e) {

}

void StateMinesweeper::update() {

}

void StateMinesweeper::draw() {
  SDL_Renderer* renderer = RendererManager::get_renderer();

  // Draw map.

  const std::vector<std::vector<MinesweeperCell>> cells = map.get_cells();
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
  for (std::size_t i = 0; i < cells.size(); i++) {
    for (std::size_t j = 0; j < cells[0].size(); j++) {
      std::string texture_id;
      SDL_Rect srcrect;
      SDL_Rect dstrect{ (int)j * 16, (int)i * 16, 16, 16 };

      MinesweeperCell cell = cells[i][j];

      if (cell.is_dug() && cell.is_mine()) { // draw mine
        texture_id = "minesweeper_sprites";
        srcrect = { 86, 50, 16, 16 };
      } else if (cell.is_dug()) { // draw number of around mines.
        texture_id = "minesweeper_sprites";
        switch (cell.around_mines_num()) {
          case 0:
            srcrect = { 18, 50, 16, 16 };
            break;
          case 1:
            srcrect = { 1, 67, 16, 16 };
            break;
          case 2:
            srcrect = { 18, 67, 16, 16 };
            break;
          case 3:
            srcrect = { 35, 67, 16, 16 };
            break;
          case 4:
            srcrect = { 52, 67, 16, 16 };
            break;
          case 5:
            srcrect = { 69, 67, 16, 16 };
            break;
          case 6:
            srcrect = { 86, 67, 16, 16 };
            break;
          case 7:
            srcrect = { 103, 67, 16, 16 };
            break;
          case 8:
            srcrect = { 120, 67, 16, 16 };
            break;
          default:
            break;
        }
      } else if (cell.get_mark() == none) { // draw mark "none"
        texture_id = "minesweeper_sprites";
        srcrect = { 1, 50, 16, 16 };
      } else if (cell.get_mark() == certain) { // draw mark "certain"
        texture_id = "minesweeper_sprites";
        srcrect = { 35, 50, 16, 16 };
      } else if (cell.get_mark() == uncertain) { // draw mark "uncertain"
        texture_id = "minesweeper_sprites";
        srcrect = { 52, 50, 16, 16 };
      }

      TextureManager::draw(renderer, "minesweeper_sprites", &srcrect, &dstrect);
    }
  }
}

void StateMinesweeper::cleanup() {

}
