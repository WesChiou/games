#include <iostream>
#include <stdexcept>
#include "../include/engine.hpp"

namespace engine {
  bool init(uint32_t sdl_flags, int img_flags) {
    if (SDL_Init(sdl_flags) != 0) {
      std::cerr << "SDL_Init has failed: " << SDL_GetError() << std::endl;
      return false;
    }

    if (IMG_Init(img_flags) == 0) {
      std::cerr << "IMG_Init has failed: " << SDL_GetError() << std::endl;
      return false;
    }

    #ifdef USE_SDL_TTF
    if (TTF_Init() != 0) {
      std::cerr << "TTF_Init has failed: " << TTF_GetError() << std::endl;
      return false;
    }
    #endif

    return true;
  }

  void quit() {
    #ifdef USE_SDL_TTF
    TTF_Quit();
    #endif

    IMG_Quit();
    SDL_Quit();
  }

  HWND create_window(const char *title, int x, int y, int w, int h, uint32_t flags) {
    SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!window) {
      throw std::runtime_error("SDL_CreateWindow has failed: " + std::string(SDL_GetError()));
    }

    HWND hwnd{ window, SDL_DestroyWindow };
    return hwnd;
  }

  void destroy_window(HWND hwnd) {
    hwnd.reset();
  }

  void set_window_size(HWND hwnd, int w, int h) {
    if (!hwnd) return;

    SDL_SetWindowSize(hwnd.get(), w, h);
  }

  void set_window_title(HWND hwnd, const char *title) {
    if (!hwnd) return;

    SDL_SetWindowTitle(hwnd.get(), title);
  }

  void set_window_icon(HWND hwnd, const char *file) {
    if (!hwnd) return;

    SDL_Surface* icon = IMG_Load(file);
    if (!icon) {
      std::cerr << "IMG_Load has failed: " << SDL_GetError() << std::endl;
      return;
    }

    SDL_SetWindowIcon(hwnd.get(), icon);
    SDL_FreeSurface(icon);
  }

  HRDR create_renderer(HWND hwnd, int index, uint32_t flags) {
    if (!hwnd) return nullptr;

    SDL_Renderer* renderer = SDL_CreateRenderer(hwnd.get(), index, flags);
    if (!renderer) {
      throw std::runtime_error("SDL_CreateRenderer has failed: " + std::string(SDL_GetError()));
    }

    HRDR hrdr{ renderer, SDL_DestroyRenderer };
    return hrdr;
  }

  void destroy_renderer(HRDR hrdr) {
    hrdr.reset();
  }

  HTEX create_texture(HRDR hrdr, const char* file) {
    if (!hrdr) return nullptr;

    SDL_Texture* texture = IMG_LoadTexture(hrdr.get(), file);
    if (!texture) {
      throw std::runtime_error("IMG_LoadTexture has failed: " + std::string(SDL_GetError()));
    }

    HTEX htex{ texture, SDL_DestroyTexture };
    return htex;
  }

  #ifdef USE_SDL_TTF
  HTEX create_texture(HRDR hrdr, HFONT hfont, const char* text, Color fg, uint32_t wrap_length) {
    if (!hrdr) return nullptr;

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(hfont.get(), text, fg, wrap_length);
    if (!surface) {
      throw std::runtime_error("TTF_RenderUTF8_Blended_Wrapped has failed: " + std::string(TTF_GetError()));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(hrdr.get(), surface);
    SDL_FreeSurface(surface);
    if (!texture) {
      throw std::runtime_error("SDL_CreateTextureFromSurface has failed: " + std::string(SDL_GetError()));
    }

    HTEX htex{ texture, SDL_DestroyTexture };
    return htex;
  }

  HFONT open_font(const char* file, int ptsize) {
    TTF_Font* font = TTF_OpenFont(file, ptsize);
    if (!font) {
      throw std::runtime_error("TTF_OpenFont has failed: " + std::string(TTF_GetError()));
    }

    HFONT hfont { font, TTF_CloseFont };
    return hfont;
  }

  void close_font(HFONT hfont) {
    hfont.reset();
  }
  #endif

  uint32_t register_userevent() {
    uint32_t type = SDL_RegisterEvents(1);
    if (type == (uint32_t) - 1) {
      std::cerr << "SDL_RegisterEvents has failed: " << SDL_GetError() << std::endl;
    }
    return type;
  }

  uint32_t get_userevent_type() {
    static uint32_t type = register_userevent();
    return type;
  }

  void trigger_userevent(UserEventCode code, void* data1, void* data2) {
    SDL_Event event;
    SDL_zero(event);
    event.type = get_userevent_type();
    event.user.code = static_cast<int>(code);
    event.user.data1 = data1;
    event.user.data2 = data2;

    SDL_PushEvent(&event);
  }
}  // namespace engine
