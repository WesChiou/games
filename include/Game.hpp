#ifndef _INCLUDE_GAME_HPP_
#define _INCLUDE_GAME_HPP_

#include <vector>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "Handle.hpp"
#include "handles.hpp"
#include "State.hpp"

class Game {
public:
  Game();
  Game(uint32_t flags);
  ~Game();

  // Create a window with the specified position, dimensions, and flags.
  // Params is same as SDL_CreateWindow()
  WindowHandle create_window(const char *title, int x, int y, int w, int h, uint32_t flags);

  // Destroy window by SDL_DestroyWindow()
  void destroy_window(WindowHandle hwnd);

  // Set/Change a window's title by SDL_SetWindowTitle()
  void set_window_title(WindowHandle hwnd, const char *title);

  // Set/Change a window's icon by SDL_SetWindowIcon() & SDL_LoadBMP();
  // NOTE: .bmp SUPPORTED ONLY.
  // TODO: 任务栏不会出现 bmp 图标
  void set_window_icon(WindowHandle hwnd, const char *file);

  // Create a 2D rendering context for a window.
  // Params is same as SDL_CreateRenderer(), except WindowHandle is used instead of SDL_Window*
  RendererHandle create_renderer(WindowHandle hwnd, int index, uint32_t flags);

  // Destroy a renderer by SDL_DestroyRenderer()
  void destroy_renderer(RendererHandle hrdr);

  // Start the game loop.
  void start(RendererHandle hrdr);

  void push_state(std::string name, std::unique_ptr<State> state);

  void pop_state();

  void remove_state(std::string name);

private:
  bool running{false};
  int real_time_fps{0};

  std::vector<std::pair<std::string, std::unique_ptr<State>>> states;

  void handle_events();
  void update();
  void draw(RendererHandle hrdr);
  void quit();
};

#endif
