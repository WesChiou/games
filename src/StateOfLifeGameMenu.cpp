#include <iostream>
#include <memory>
#include "../include/StateOfStartMenu.hpp"
#include "../include/StateOfLifeGame.hpp"
#include "../include/StateOfLifeGameMenu.hpp"

StateOfLifeGameMenu::StateOfLifeGameMenu(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager)
: hrdr(hrdr), texture_manager(texture_manager) {
  std::cout << "StateOfLifeGameMenu" << std::endl;
}

StateOfLifeGameMenu::~StateOfLifeGameMenu() {
  std::cout << "~StateOfLifeGameMenu" << std::endl;
}

void StateOfLifeGameMenu::load() {
  std::optional<HTEX> op_continue_game_label = texture_manager->create_i18n_label("zh", "pausemenu_continue", alibabafont);
  if (op_continue_game_label.has_value()) {
    continue_game_label = op_continue_game_label.value();
  }

  std::optional<HTEX> op_new_game_label = texture_manager->create_i18n_label("zh", "pausemenu_newgame", alibabafont);
  if (op_new_game_label.has_value()) {
    new_game_label = op_new_game_label.value();
  }

  std::optional<HTEX> op_back_startmenu_label = texture_manager->create_i18n_label("zh", "pausemenu_backtostartmenu", alibabafont);
  if (op_back_startmenu_label.has_value()) {
    back_startmenu_label = op_back_startmenu_label.value();
  }
}

void StateOfLifeGameMenu::handle_event(SDL_Event& event, StateManager& state_manager) {
  switch (event.type) {
    case SDL_KEYDOWN:
      {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            {
              state_manager.edit_state("lifegamemenu", {
                .need_to_fuse = true,
              });
              state_manager.edit_state("lifegame", {});
            }
            break;
          default:
            break;
        }
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      {
        if (event.button.button == SDL_BUTTON_LEFT) {
          SDL_Point p{ event.button.x, event.button.y };

          if (SDL_PointInRect(&p, &rect_continue_game)) {
            state_manager.edit_state("lifegamemenu", {
              .need_to_fuse = true,
            });
            state_manager.edit_state("lifegame", {});
          } else if (SDL_PointInRect(&p, &rect_new_game)) {
            state_manager.edit_state("lifegamemenu", {
              .need_to_fuse = true,
            });
            state_manager.add_state({
              .state = std::make_shared<StateOfLifeGame>(hrdr, texture_manager),
              .unique_name = "lifegame",
            });
          } else if (SDL_PointInRect(&p, &rect_back_startmenu)) {
            state_manager.edit_state("lifegamemenu", {
              .need_to_fuse = true,
            });
            state_manager.edit_state("lifegame", {
              .need_to_fuse = true,
            });
            state_manager.add_state({
              .state = std::make_shared<StateOfStartMenu>(hrdr, texture_manager),
              .unique_name = "startmenu",
            });
          }
        }
      }
      break;
    default:
      break;
  }
}

void StateOfLifeGameMenu::update() {
}

void StateOfLifeGameMenu::render() {
  const SDL_Rect rect_menu{ 150, 150, 340, 180 };
  SDL_SetRenderDrawColor(hrdr.get(), 173, 216, 230, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_menu);
  SDL_SetRenderDrawColor(hrdr.get(), 255, 255, 255, 255);
  SDL_RenderDrawRect(hrdr.get(), &rect_menu);

  SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);

  SDL_RenderFillRect(hrdr.get(), &rect_continue_game);
  if (continue_game_label) {
    SDL_Rect dstrect{ rect_continue_game.x, rect_continue_game.y, 0, 0 };
    SDL_QueryTexture(continue_game_label.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), continue_game_label.get(), nullptr, &dstrect);
  }

  SDL_RenderFillRect(hrdr.get(), &rect_new_game);
  if (new_game_label) {
    SDL_Rect dstrect{ rect_new_game.x, rect_new_game.y, 0, 0 };
    SDL_QueryTexture(new_game_label.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), new_game_label.get(), nullptr, &dstrect);
  }

  SDL_RenderFillRect(hrdr.get(), &rect_back_startmenu);
  if (back_startmenu_label) {
    SDL_Rect dstrect{ rect_back_startmenu.x, rect_back_startmenu.y, 0, 0 };
    SDL_QueryTexture(back_startmenu_label.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), back_startmenu_label.get(), nullptr, &dstrect);
  }

  SDL_Point mouse{ 0, 0 };
  SDL_GetMouseState(&mouse.x, &mouse.y);
  SDL_SetRenderDrawColor(hrdr.get(), 255, 255, 255, 255);
  if (SDL_PointInRect(&mouse, &rect_new_game)) {
    SDL_RenderDrawRect(hrdr.get(), &rect_new_game);
  } else if (SDL_PointInRect(&mouse, &rect_continue_game)) {
    SDL_RenderDrawRect(hrdr.get(), &rect_continue_game);
  } else if (SDL_PointInRect(&mouse, &rect_back_startmenu)) {
    SDL_RenderDrawRect(hrdr.get(), &rect_back_startmenu);
  }
}

void StateOfLifeGameMenu::unload() {
  std::cout << "StateOfLifeGameMenu unload()" << std::endl;
}
