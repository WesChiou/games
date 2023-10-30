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
  std::optional<HTEX> op_label_quit = texture_manager->create_i18n_label("zh", "startmenu_quit", alibabafont);
  if (op_label_quit.has_value()) {
    label_quit = op_label_quit.value();
  }

  std::optional<HTEX> op_label_examplegame = texture_manager->create_i18n_label("zh", "startmenu_examplegame", alibabafont);
  if (op_label_examplegame.has_value()) {
    label_examplegame = op_label_examplegame.value();
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

          if (SDL_PointInRect(&p, &rect_examplegame)) {
            state_manager.edit_state("startmenu", {
              .need_to_fuse = true,
            });
            state_manager.add_state({
              .state = std::make_shared<StateOfExampleGame>(hrdr, texture_manager),
              .unique_name = "examplegame",
            });
          } else if (SDL_PointInRect(&p, &rect_quit)) {
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
  SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_menu);

  SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_examplegame);
  if (label_examplegame) {
    SDL_Rect dstrect{ rect_examplegame.x, rect_examplegame.y, 0, 0 };
    SDL_QueryTexture(label_examplegame.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), label_examplegame.get(), nullptr, &dstrect);
  }

  SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);
  SDL_RenderFillRect(hrdr.get(), &rect_quit);
  if (label_quit) {
    SDL_Rect dstrect{ rect_quit.x, rect_quit.y, 0, 0 };
    SDL_QueryTexture(label_quit.get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), label_quit.get(), nullptr, &dstrect);
  }

  SDL_Point mouse{ 0, 0 };
  SDL_GetMouseState(&mouse.x, &mouse.y);
  SDL_SetRenderDrawColor(hrdr.get(), 255, 255, 255, 255);
  if (SDL_PointInRect(&mouse, &rect_examplegame)) {
    SDL_RenderDrawRect(hrdr.get(), &rect_examplegame);
  } else if (SDL_PointInRect(&mouse, &rect_quit)) {
    SDL_RenderDrawRect(hrdr.get(), &rect_quit);
  }
}

void StateOfStartMenu::unload() {
  std::cout << "StateOfStartMenu unload()" << std::endl;
}
