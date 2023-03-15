#include "../include/StateMachine.hpp"
#include "../include/MouseClickEvent.hpp"

void StateMachine::start(HRDR hrdr) {
  running = true;

  while (running) {
    uint64_t loop_start = SDL_GetPerformanceCounter();

    handle_events();  // quit() here.
    update();
    draw(hrdr);

    // Calculate real time fps.
    float loop_ms = (SDL_GetPerformanceCounter() - loop_start) / static_cast<float>(SDL_GetPerformanceFrequency());
    real_time_fps = 1 / loop_ms;
  }
}

void StateMachine::push_state(std::string name, std::unique_ptr<State> state) {
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

void StateMachine::pop_state() {
  if (!states.empty()) {
    states.back().second->cleanup();
    states.pop_back();
  }
}

void StateMachine::remove_state(std::string name) {
  for (auto it = states.rbegin(); it != states.rend(); ++it) {
    if (it->first == name) {
      states.erase((it + 1).base());
      return;
    }
  }
}

void StateMachine::init() {
  event_handlers.emplace_back(std::make_unique<MouseClickEvent>());
}

void StateMachine::handle_events() {
  SDL_Event event;

  SDL_StopTextInput();

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

void StateMachine::update() {
  for (const auto& pair : states) {
    if (!pair.second->is_pause()) {
      pair.second->update();
    }
  }
}

void StateMachine::draw(HRDR hrdr) {
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

void StateMachine::quit() {
  running = false;

  // Cleanup all states.
  for (const auto& pair : states) {
    pair.second->cleanup();
  }
}
