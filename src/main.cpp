#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <random>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <optional>
#include "../include/nlohmann/json.hpp"
#include "../include/alias.hpp"
#include "../include/userevent.hpp"
#include "../include/TextureRegion.hpp"
#include "../include/TextureManager.hpp"
#include "../include/FontStyle.hpp"
#include "../include/State.hpp"
#include "../include/StateOfStartMenu.hpp"
#include "../include/StateOfExampleGameMenu.hpp"
#include "../include/StateOfExampleGame.hpp"

int main(int argc, char *args[]) {
  // Initialize SDL, SDL_image, etc.
  SDL_Init(SDL_INIT_EVERYTHING);

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    throw std::runtime_error("IMG_Init Has Failed: " + std::string(SDL_GetError()));
  }

  if (TTF_Init() != 0) {
    throw std::runtime_error("TTF_Init Has Failed: " + std::string(TTF_GetError()));
  }

  // Create Window.
  SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
  if (!window) {
    throw std::runtime_error("SDL_CreateWindow Has Failed: " + std::string(SDL_GetError()));
  }
  HWND hwnd{ window, SDL_DestroyWindow };

  // Create Renderer.
  SDL_Renderer* renderer = SDL_CreateRenderer(hwnd.get(), -1, SDL_RENDERER_ACCELERATED);  // SDL_RENDERER_PRESENTVSYNC
  if (!renderer) {
    throw std::runtime_error("SDL_CreateRenderer Has Failed: " + std::string(SDL_GetError()));
  }
  HRDR hrdr{ renderer, SDL_DestroyRenderer };

  std::shared_ptr<TextureManager> texture_manager = std::make_shared<TextureManager>(hrdr, "res/textureregions.json", "res/i18n.json");

  StateManager state_manager;

  state_manager.add_state({
    .state = std::make_shared<StateOfStartMenu>(hrdr, texture_manager),
    .unique_name = "startmenu",
  });

  // Game loop stuff.
  uint32_t fps_expected{ 60 };
  float frame_duration{ 1000.0f / fps_expected };
  int fps_realtime{ 0 };
  bool quit{ false };
  while (!quit) {
    const uint64_t frame_start = SDL_GetTicks64();

    // Handle events
    SDL_Event event;
    SDL_StopTextInput();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
        break;
      }

      if (event.type == SDL_USEREVENT) {
        if (event.user.code == static_cast<int>(userevent::Code::quit)) {
          quit = true;
          break;
        }
      }

      state_manager.handle_event(event);
    }

    // Update
    state_manager.update();

    // Draw
    SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 0);
    SDL_RenderClear(hrdr.get());
    // -----Draw Start-----
    state_manager.render();
    // -----Draw End-----
    SDL_RenderPresent(hrdr.get());

    // FPS stuff
    while (SDL_GetTicks64() < frame_start + frame_duration) {
      // Do nothing until timeout has elapsed.
      // This method is better than SDL_Delay for capping frame rate.
    }
    fps_realtime = ceil(1000.0f / (SDL_GetTicks64() - frame_start));
  }

  // Quit SDL, SDL_image, etc.
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();

  return 0;
}
