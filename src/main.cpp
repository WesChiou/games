#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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
#include "../include/TextureRegion.hpp"
#include "../include/TextureManager.hpp"
#include "../include/FontStyle.hpp"

using json = nlohmann::json;

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
  SDL_Renderer* renderer = SDL_CreateRenderer(hwnd.get(), -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC
  if (!renderer) {
    throw std::runtime_error("SDL_CreateRenderer Has Failed: " + std::string(SDL_GetError()));
  }
  HRDR hrdr{ renderer, SDL_DestroyRenderer };

  TextureManager texture_manager{ hrdr, "res/textureregions.json" };

  FontStyle alibabafont {
    .source = "res/AlibabaPuHuiTi/AlibabaPuHuiTi-3-55-Regular.ttf",
    .render_mode = FontRenderMode::Blended,
    .fg = { 255, 255, 255, 255 },
    .bg = { 25, 95, 125, 255 },
    .size = 24,
    // .outline = 1,
    .align = TTF_WRAPPED_ALIGN_CENTER,
    // .style = TTF_STYLE_UNDERLINE,
    .wrap_length = 160,
  };
  std::optional<HTEX> three_kingdom_label = texture_manager.create_label("话说天下大势，分久必合，合久必分。", alibabafont);
  std::optional<HTEX> continue_game_label = texture_manager.create_label("继续游戏", alibabafont);
  std::optional<HTEX> new_game_label = texture_manager.create_label("新游戏", alibabafont);

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
    }

    // Update
    {
      alibabafont.fg.b++;
      if (alibabafont.fg.b > 255) {
        alibabafont.fg.b = 0;
      }
    }

    // Draw
    SDL_SetRenderDrawColor(hrdr.get(), 0, 0, 0, 0);
    SDL_RenderClear(hrdr.get());
    // -----Draw Start-----
    // Draw test tileset.
    for (int id = 1; id <= 57; id++) {
      std::optional<TextureRegion> tr = texture_manager.get_texture_region(id);
      if (tr.has_value()) {
        SDL_RenderCopy(hrdr.get(), tr.value().htex.get(), &tr.value().region, &tr.value().region);
      }
    }

    // Draw menu.
    const SDL_Rect rect_menu{ 150, 150, 340, 180 };
    SDL_SetRenderDrawColor(hrdr.get(), 173, 216, 230, 255);
    SDL_RenderFillRect(hrdr.get(), &rect_menu);
    SDL_SetRenderDrawColor(hrdr.get(), 255, 255, 255, 255);
    SDL_RenderDrawRect(hrdr.get(), &rect_menu);

    SDL_Rect rect_continue_game{ 150 + 20, 150 + 20, 200, 50 };
    SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);
    SDL_RenderFillRect(hrdr.get(), &rect_continue_game);
    if (continue_game_label.has_value()) {
      SDL_Rect dstrect{ rect_continue_game.x, rect_continue_game.y, 0, 0 };
      SDL_QueryTexture(continue_game_label.value().get(), NULL, NULL, &dstrect.w, &dstrect.h);
      SDL_RenderCopy(hrdr.get(), continue_game_label.value().get(), nullptr, &dstrect);
    }

    SDL_Rect rect_new_game{ 150 + 20, 150 + 20 + 50 + 20, 200, 50 };
    SDL_SetRenderDrawColor(hrdr.get(), 25, 95, 125, 255);
    SDL_RenderFillRect(hrdr.get(), &rect_new_game);
    if (new_game_label.has_value()) {
      SDL_Rect dstrect{ rect_new_game.x, rect_new_game.y, 0, 0 };
      SDL_QueryTexture(new_game_label.value().get(), NULL, NULL, &dstrect.w, &dstrect.h);
      SDL_RenderCopy(hrdr.get(), new_game_label.value().get(), nullptr, &dstrect);
    }

    // Draw fps.
    auto fps_label = texture_manager.create_label(std::to_string(fps_realtime), alibabafont);
    if (fps_label.has_value()) {
      SDL_Rect dstrect{ 500, 0, 0, 0 };
      SDL_QueryTexture(fps_label.value().get(), NULL, NULL, &dstrect.w, &dstrect.h);
      SDL_RenderCopy(hrdr.get(), fps_label.value().get(), nullptr, &dstrect);
    }

    // Draw test label.
    if (three_kingdom_label.has_value()) {
      SDL_Rect dstrect{ 0, 380, 200, 200 };
      SDL_QueryTexture(three_kingdom_label.value().get(), NULL, NULL, &dstrect.w, &dstrect.h);
      SDL_RenderCopy(hrdr.get(), three_kingdom_label.value().get(), nullptr, &dstrect);
    }
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
