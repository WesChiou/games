#include <iostream>
#include "../include/StateOfExampleGame.hpp"
#include "../include/StateOfPauseMenu.hpp"

StateOfExampleGame::StateOfExampleGame(HRDR hrdr, std::shared_ptr<TextureManager> texture_manager)
: hrdr(hrdr), texture_manager(texture_manager) {
  std::cout << "StateOfExampleGame" << std::endl;
}

StateOfExampleGame::~StateOfExampleGame() {
  std::cout << "~StateOfExampleGame" << std::endl;
}

void StateOfExampleGame::load() {
  std::cout << "StateOfExampleGame load()" << std::endl;
}

void StateOfExampleGame::handle_event(SDL_Event& event, StateManager& state_manager) {
  switch (event.type) {
    case SDL_KEYDOWN:
      {
        switch (event.key.keysym.sym) {
          case SDLK_SPACE:
            pause = !pause;
            break;
          case SDLK_ESCAPE:
            {
              state_manager.edit_state("examplegame", {
                .should_handle_event = false,
                .should_update = false,
              });
              state_manager.add_state({
                .state = std::make_shared<StateOfPauseMenu>(hrdr, texture_manager),
                .unique_name = "pausemenu",
              });
            }
            break;
          default:
            break;
        }
      }
      break;
    default:
      break;
  }
}

void StateOfExampleGame::update() {
  if (!pause) {
    game.update();
  }
}

void StateOfExampleGame::render() {
  auto msg_label = texture_manager->create_label(std::to_string(game.get_msg()), alibabafont);
  if (msg_label.has_value()) {
    SDL_Rect dstrect{ 0, 100, 0, 0 };
    SDL_QueryTexture(msg_label.value().get(), NULL, NULL, &dstrect.w, &dstrect.h);
    SDL_RenderCopy(hrdr.get(), msg_label.value().get(), nullptr, &dstrect);
  }
}

void StateOfExampleGame::unload() {
  std::cout << "StateOfExampleGame unload()" << std::endl;
}
