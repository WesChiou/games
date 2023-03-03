#ifndef _INCLUDE_EVENT_HPP_
#define _INCLUDE_EVENT_HPP_

#include <cstdint>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "alias.hpp"

namespace engine {
  enum class UserEventCode {
    mouse_click,
  };

  // See SDL_Init and IMG_Init.
  bool init(uint32_t sdl_flags, int img_flags);

  // See IMG_Quit and SDL_Quit.
  void quit();

  // Create a window with the specified position, dimensions, and flags.
  // Params is same as SDL_CreateWindow().
  HWND create_window(const char *title, int x, int y, int w, int h, uint32_t flags);

  // Destroy a window by SDL_DestroyWindow() manually.
  void destroy_window(HWND hwnd);

  // Set/Change a window's title by SDL_SetWindowTitle().
  void set_window_title(HWND hwnd, const char *title);

  // Set/Change a window's icon by SDL_SetWindowIcon() & SDL_LoadBMP();
  // NOTE: .bmp SUPPORTED ONLY.
  void set_window_icon(HWND hwnd, const char *file);

  // Create a 2D rendering context for a window.
  // Params is same as SDL_CreateRenderer(), except HWND is used instead of SDL_Window*.
  HRDR create_renderer(HWND hwnd, int index, uint32_t flags);

  // Destroy a renderer by SDL_DestroyRenderer() manually.
  void destroy_renderer(HRDR hrdr);

  // Create a SDL_Texture by IMG_LoadTexture().
  HTEX create_texture(HRDR hrdr, const char* file);

  // Create a SDL_Texture by SDL_ttf from given font.
  HTEX create_texture(HRDR hrdr, HFONT hfont, const char* text, Color fg, uint32_t wrap_length);

  // Open a font by TTF_OpenFont().
  HFONT open_font(const char* file, int ptsize);

  // Close a font by TTF_CloseFont() manually.
  void close_font(HFONT hfont);

  uint32_t register_userevent();

  uint32_t get_registered_type();

  void trigger_userevent(UserEventCode code, void* data1, void* data2);
}

#endif
