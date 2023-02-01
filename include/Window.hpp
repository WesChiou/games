#ifndef _INCLUDE_WINDOW_HPP_
#define _INCLUDE_WINDOW_HPP_

#include <string>
#include <stdexcept> // runtime_error

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// C++ singleton with arguments.
// https://stackoverflow.com/a/52308483/8198710
class Window {
public:
  static bool init(std::string title = "") {
    instance_impl(title);
    return true;
  };

  static Window& instance() {
    return instance_impl();
  };

  static void cleanup() {
    SDL_DestroyWindow(instance().window);
  };

  static SDL_Window* const get_window() {
    return instance().window;
  };

  static void set_title(std::string title) {
    SDL_SetWindowTitle(instance().window, title.c_str());
  };

  static void set_icon(std::string icon_path) {
    SDL_Surface* icon = IMG_Load(icon_path.c_str());
    if (icon) {
      SDL_SetWindowIcon(instance().window, icon);
    }
  };

  Window(Window const&) = delete;
  Window& operator = (Window const&) = delete;

private:
  SDL_Window* window;

  static Window& instance_impl(std::string title = "") {
    static Window instance{ title };
    return instance;
  };

  Window(std::string title) {
    window = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      // TODO: more arguments need pass by constructor.
      640,
      520,
      0
    );

    if (!window) {
      throw std::runtime_error{ "Window HAS FAILED TO CREATE WINDOW." };
    }
  };
};

#endif
