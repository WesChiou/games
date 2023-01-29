#include <stdexcept> // runtime_error

#include "WindowManager.hpp"
#include "RendererManager.hpp"
#include "Game.hpp"

void Game::init(std::string title = "") {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error{ "SDL_Init HAS FAILED." };
  }

  WindowManager::init(title);

  RendererManager::init(WindowManager::get_window());
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

void Game::push_state(IState* state) {
  states.push_back(state);
  state->init();
}

void Game::pop_state() {
  if (states.empty()) return;

  states.back()->cleanup();
  states.pop_back();
}

void Game::handle_events() {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit();
      return;
    }

    for (auto state: states) {
      if (!state->sleep) {
        state->handle_event(&e);
      }
    }
  }
}

void Game::update() {
  for (auto state: states) {
    if (!state->pause) {
      state->update();
    }
  }
}

void Game::draw() {
  SDL_Renderer* renderer = RendererManager::get_renderer();

  // Erase the last frame.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (auto state: states) {
    if (!state->invisible) {
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

  WindowManager::cleanup();

  RendererManager::cleanup();

  SDL_Quit();
}
