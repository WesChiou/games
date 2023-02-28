#ifndef _INCLUDE_EVENT_HPP_
#define _INCLUDE_EVENT_HPP_

#include <cstdint>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine {
  enum class UserEventCode {
    mouse_click,
  };

  // See SDL_Init and IMG_Init
  bool init(uint32_t sdl_flags, int img_flags);

  // See IMG_Quit and SDL_Quit
  void quit();

  // Create a window with the specified position, dimensions, and flags.
  // Params is same as SDL_CreateWindow()
  std::shared_ptr<SDL_Window> create_window(const char *title, int x, int y, int w, int h, uint32_t flags);

  // Destroy window by SDL_DestroyWindow()
  void destroy_window(std::shared_ptr<SDL_Window> hwnd);

  // Set/Change a window's title by SDL_SetWindowTitle()
  void set_window_title(std::shared_ptr<SDL_Window> hwnd, const char *title);

  // Set/Change a window's icon by SDL_SetWindowIcon() & SDL_LoadBMP();
  // NOTE: .bmp SUPPORTED ONLY.
  void set_window_icon(std::shared_ptr<SDL_Window> hwnd, const char *file);

  // Create a 2D rendering context for a window.
  // Params is same as SDL_CreateRenderer(), except std::shared_ptr<SDL_Window> is used instead of SDL_Window*
  std::shared_ptr<SDL_Renderer> create_renderer(std::shared_ptr<SDL_Window> hwnd, int index, uint32_t flags);

  // Destroy a renderer by SDL_DestroyRenderer()
  void destroy_renderer(std::shared_ptr<SDL_Renderer> hrdr);

  uint32_t register_userevent();

  uint32_t get_registered_type();

  void trigger_userevent(UserEventCode code, void* data1, void* data2);
}

#endif
