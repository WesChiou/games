#ifndef _INCLUDE_WINDOWMANAGER_HPP_
#define _INCLUDE_WINDOWMANAGER_HPP_

#include <string>
#include <stdexcept> // runtime_error

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

  static void set_title(std::string title) {
    SDL_SetWindowTitle(instance().window, title.c_str());
  };

  static void set_icon(std::string icon_path) {
    SDL_Surface* icon = IMG_Load(icon_path.c_str());
    if (icon) {
      SDL_SetWindowIcon(instance().window, icon);
    }
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
      // TODO: more arguments need pass by constructor.
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
