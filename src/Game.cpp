#include <stdexcept> // runtime_error

#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "Renderer.hpp"
#include "CustomEvent.hpp"
#include "MouseListener.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"

void Game::init(std::string title = "") {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error{ "SDL_Init HAS FAILED." };
  }

  // Initialize SDL_image
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    throw std::runtime_error{ "IMG_Init HAS FAILED." };
  }

  if (!Window::init(title)) {
    throw std::runtime_error{ "Window::init() HAS FAILED." };
  }

  if (!Renderer::init(Window::get_window())) {
    throw std::runtime_error{ "Renderer::init() HAS FAILED." };
  }

  if (!CustomEvent::init()) {
    throw std::runtime_error{ "CustomEvent::init() HAS FAILED." };
  }

  if (!MouseListener::init()) {
    throw std::runtime_error{ "MouseListener::init() HAS FAILED." };
  }

  if (!TextureManager::init()) {
    throw std::runtime_error{ "TextureManager::init() HAS FAILED." };
  }
}

void Game::start() {
  running = true;

  while (running) {
    Uint64 loop_start = SDL_GetPerformanceCounter();

    handle_events(); // quit() here.
    update();
    draw();

    // Calculate real time fps.
    float loop_ms = (SDL_GetPerformanceCounter() - loop_start) / (float)SDL_GetPerformanceFrequency();
    real_time_fps = 1 / loop_ms;
  }
}

void Game::push_state(State* state) {
  states.push_back(state);
  state->init();
}

void Game::pop_state() {
  if (states.empty()) return;

  states.back()->cleanup();
  states.pop_back();
}

void Game::set_title(std::string title) {
  Window::set_title(title);
}

void Game::set_icon(std::string icon_path) {
  Window::set_icon(icon_path);
}

void Game::handle_events() {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit();
      return;
    }

    for (auto state: states) {
      if (!state->is_sleep()) {
        state->handle_event(&e);
      }
    }
  }
}

void Game::update() {
  for (auto state: states) {
    if (!state->is_pause()) {
      state->update();
    }
  }
}

void Game::draw() {
  SDL_Renderer* renderer = Renderer::get_renderer();

  // Erase the last frame.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (auto state: states) {
    if (!state->is_invisible()) {
      state->draw();
    }
  }

  // Render the current frame.
  SDL_RenderPresent(renderer);
}

void Game::quit() {
  running = false;

  // Cleanup all states.
  for (auto state: states) {
    state->cleanup();
  }
  states.clear();

  Window::cleanup();

  Renderer::cleanup();

  CustomEvent::cleanup();

  MouseListener::cleanup();

  TextureManager::cleanup();

  IMG_Quit();
  SDL_Quit();
}
