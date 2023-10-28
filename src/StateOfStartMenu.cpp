#include <iostream>
#include <memory>
#include <stdexcept>
#include "../include/userevent.hpp"
#include "../include/StateOfStartMenu.hpp"
#include "../include/StateOfExampleGame.hpp"

StateOfStartMenu::StateOfStartMenu(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager)
: hrdr(hrdr), texture_manager(texture_manager) {
  std::cout << "StateOfStartMenu" << std::endl;
}

StateOfStartMenu::~StateOfStartMenu() {
  std::cout << "~StateOfStartMenu" << std::endl;
}

void StateOfStartMenu::load() {
  std::optional<HTEX> op_quit_game_label = texture_manager->create_label("退出游戏", alibabafont);
  if (op_quit_game_label.has_value()) {
    quit_game_label = op_quit_game_label.value();
  }

  std::optional<HTEX> op_new_game_label = texture_manager->create_label("新游戏", alibabafont);
  if (op_new_game_label.has_value()) {
    new_game_label = op_new_game_label.value();
  }
}

void StateOfStartMenu::handle_event(SDL_Event& event, StateManager& state_manager) {
  switch (event.type) {
    case SDL_KEYDOWN:
      {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            userevent::trigger(userevent::Code::quit, nullptr, nullptr);
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

          if (SDL_PointInRect(&p, &rect_new_game)) {
            state_manager.edit_state("startmenu", {
              .need_to_fuse = true,
            });
            state_manager.add_state({
              .state = std::make_shared<StateOfExampleGame>(hrdr, texture_manager),
              .unique_name = "examplegame",
            });
          } else if (SDL_PointInRect(&p, &rect_quit_game)) {
            userevent::trigger(userevent::Code::quit, nullptr, nullptr);
          }
        }
      }
      break;
    default:
      break;
  }
}

void StateOfStartMenu::update() {
}

void StateOfStartMenu::render() {
  const SDL_Rect rect_menu{ 0, 0, 640, 480 };
  SDL_SetRenderDrawColor(hrdr.get(), 255, 255, 255, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_menu);

  SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_new_game);
  if (new_game_label) {
    SDL_Rect dstrect{ rect_new_game.x, rect_new_game.y, 0, 0 };
    SDL_QueryTexture(new_game_label.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), new_game_label.get(), nullptr, &dstrect);
  }

  SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_quit_game);
  if (quit_game_label) {
    SDL_Rect dstrect{ rect_quit_game.x, rect_quit_game.y, 0, 0 };
    SDL_QueryTexture(quit_game_label.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), quit_game_label.get(), nullptr, &dstrect);
  }
}

void StateOfStartMenu::unload() {
  std::cout << "StateOfStartMenu unload()" << std::endl;
}
