#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "Game.hpp"
#include "MouseClickEvent.hpp"

WindowHandle Game::create_window(const char *title, int x, int y, int w, int h, uint32_t flags) {
  SDL_Window* pwnd = SDL_CreateWindow(title, x, y, w, h, flags);
  if (!pwnd) {
    std::cerr << "SDL_CreateWindow has failed: " << SDL_GetError() << std::endl;
  }

  std::shared_ptr<SDL_Window> window{};
  window.reset(pwnd, SDL_DestroyWindow);

  return WindowHandle(window);
}

void Game::destroy_window(WindowHandle hwnd) {
  SDL_DestroyWindow(hwnd.get());
}

void Game::set_window_title(WindowHandle hwnd, const char *title) {
  SDL_SetWindowTitle(hwnd.get(), title);
}

void Game::set_window_icon(WindowHandle hwnd, const char *file) {
  SDL_Surface * icon = SDL_LoadBMP(file);
  if (!icon) {
    std::cerr << "SDL_LoadBMP has failed: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_SetWindowIcon(hwnd.get(), icon);
  SDL_FreeSurface(icon);
}

RendererHandle Game::create_renderer(WindowHandle hwnd, int index, uint32_t flags) {
  SDL_Renderer* prdr = SDL_CreateRenderer(hwnd.get(), index, flags);
  if (!prdr) {
    std::cerr << "SDL_CreateRenderer has failed: " << SDL_GetError() << std::endl;
  }

  std::shared_ptr<SDL_Renderer> renderer{};
  renderer.reset(prdr, SDL_DestroyRenderer);

  return RendererHandle(renderer);
}

void Game::destroy_renderer(RendererHandle hrdr) {
  SDL_DestroyRenderer(hrdr.get());
}

void Game::start(RendererHandle hrdr) {
  running = true;

  while (running) {
    uint64_t loop_start = SDL_GetPerformanceCounter();

    handle_events(); // quit() here.
    update();
    draw(hrdr);

    // Calculate real time fps.
    float loop_ms = (SDL_GetPerformanceCounter() - loop_start) / (float)SDL_GetPerformanceFrequency();
    real_time_fps = 1 / loop_ms;
  }
}

void Game::push_state(std::string name, std::unique_ptr<State> state) {
  // Replace state if existed (by name).
  for (auto& s : states) {
    if (s.first == name) {
      s.second = std::move(state);
      s.second->init();
      return;
    }
  }

  states.emplace_back(std::make_pair(std::move(name), std::move(state)));
  states.back().second->init();
}

void Game::pop_state() {
  if (!states.empty()) {
    states.back().second->cleanup();
    states.pop_back();
  }
}

void Game::remove_state(std::string name) {
  for (auto it = states.rbegin(); it != states.rend(); ++it) {
    if (it->first == name) {
      states.erase((it + 1).base());
      return;
    }
  }
}

void Game::init() {
  event_handlers.emplace_back(std::make_unique<MouseClickEvent>());
}

void Game::handle_events() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      quit();
      return;
    }

    // Forward event to each event handlers.
    for (const auto& event_handler : event_handlers) {
      event_handler->handle_event(&event);
    }

    // Forward event to each state.
    for (const auto& pair : states) {
      if (!pair.second->is_sleep()) {
        pair.second->handle_event(&event);
      }
    }
  }
}

void Game::update() {
  for (const auto& pair : states) {
    if (!pair.second->is_pause()) {
      pair.second->update();
    }
  }
}

void Game::draw(RendererHandle hrdr) {
  auto renderer = hrdr.get();

  // Erase the last frame.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  for (const auto& pair : states) {
    if (!pair.second->is_invisible()) {
      pair.second->draw(hrdr);
    }
  }

  // Render the current frame.
  SDL_RenderPresent(renderer);
}

void Game::quit() {
  running = false;

  // Cleanup all states.
  for (const auto& pair : states) {
    pair.second->cleanup();
  }
}
