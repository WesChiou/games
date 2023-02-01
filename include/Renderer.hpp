#ifndef _INCLUDE_RENDERER_HPP_
#define _INCLUDE_RENDERER_HPP_

#include <stdexcept> // runtime_error

#include <SDL2/SDL.h>

class Renderer {
public:
  static bool init(SDL_Window* const window = nullptr) {
    if (!window) {
      return false;
    }
    instance_impl(window);
    return true;
  };

  static Renderer& instance() {
    return instance_impl();
  };

  static void cleanup() {
    SDL_DestroyRenderer(instance().renderer);
  };

  static SDL_Renderer* const get_renderer() {
    return instance().renderer;
  };

  Renderer(Renderer const&) = delete;
  Renderer& operator = (Renderer const&) = delete;

private:
  SDL_Renderer* renderer;

  static Renderer& instance_impl(SDL_Window* const window = nullptr) {
    static Renderer instance{ window };
    return instance;
  };

  Renderer(SDL_Window* const window) {
    if (!window) {
      throw std::runtime_error{ "'window' IS REQUIRED FOR Renderer." };
    }

    renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
      throw std::runtime_error{ "Renderer HAS FAILED TO CREATE RENDERER." };
    }
  };
};

#endif
