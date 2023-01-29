#ifndef _INCLUDE_WINDOWMANAGER_HPP_
#define _INCLUDE_WINDOWMANAGER_HPP_

#include <string>
#include <stdexcept> // runtime_error

#include <SDL2/SDL.h>

// C++ singleton with arguments.
// https://stackoverflow.com/a/52308483/8198710
class WindowManager {
public:
  static WindowManager& init(std::string title = "") {
    return instance_impl(&title);
  };

  static WindowManager& instance() {
    return instance_impl();
  };

  static void cleanup() {
    SDL_DestroyWindow(instance().window);
  };

  static SDL_Window* const get_window() {
    return instance().window;
  };

  WindowManager(WindowManager const&) = delete;
  WindowManager& operator = (WindowManager const&) = delete;

private:
  std::string title;
  SDL_Window* window;

  static WindowManager& instance_impl(std::string* const title = nullptr) {
    static WindowManager instance{ title };
    return instance;
  };

  WindowManager(std::string* const title)
  : title( title ? std::move(*title) : std::string{} ) {
    window = SDL_CreateWindow(
      this->title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      // TODO: more arguments.
      640,
      520,
      0
    );

    if (!window) {
      throw std::runtime_error{ "WindowManager HAS FAILED TO CREATE WINDOW." };
    }
  };
};

#endif
