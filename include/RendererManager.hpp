#ifndef _INCLUDE_RENDERERMANAGER_HPP_
#define _INCLUDE_RENDERERMANAGER_HPP_

#include <stdexcept> // runtime_error

#include <SDL2/SDL.h>

class RendererManager {
public:
  static RendererManager& init(SDL_Window* const window = nullptr) {
    return instance_impl(window);
  };

  static RendererManager& instance() {
    return instance_impl();
  };

  static void cleanup() {
    SDL_DestroyRenderer(instance().renderer);
  };

  static SDL_Renderer* const get_renderer() {
    return instance().renderer;
  };

  RendererManager(RendererManager const&) = delete;
  RendererManager& operator = (RendererManager const&) = delete;

private:
  SDL_Renderer* renderer;

  static RendererManager& instance_impl(SDL_Window* const window = nullptr) {
    static RendererManager instance{ window };
    return instance;
  };

  RendererManager(SDL_Window* const window) {
    if (!window) {
      throw std::runtime_error{ "'window' IS REQUIRED FOR RendererManager." };
    }

    renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
      throw std::runtime_error{ "RendererManager HAS FAILED TO CREATE RENDERER." };
    }
  };
};

#endif
