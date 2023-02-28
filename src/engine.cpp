#include <iostream>

#include "engine.hpp"

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

    return true;
  };

  void quit() {
    IMG_Quit();
    SDL_Quit();
  };

  HWND create_window(const char *title, int x, int y, int w, int h, uint32_t flags) {
    SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (!window) {
      throw std::runtime_error("SDL_CreateWindow has failed: " + std::string(SDL_GetError()));
    }

    HWND hwnd{ window, SDL_DestroyWindow };
    return hwnd;
  }

  void destroy_window(HWND hwnd) {
    SDL_DestroyWindow(hwnd.get());
  }

  void set_window_title(HWND hwnd, const char *title) {
    SDL_SetWindowTitle(hwnd.get(), title);
  }

  void set_window_icon(HWND hwnd, const char *file) {
    SDL_Surface* icon = SDL_LoadBMP(file);
    if (!icon) {
      std::cerr << "SDL_LoadBMP has failed: " << SDL_GetError() << std::endl;
      return;
    }

    SDL_SetWindowIcon(hwnd.get(), icon);
    SDL_FreeSurface(icon);
  }

  HRDR create_renderer(HWND hwnd, int index, uint32_t flags) {
    SDL_Renderer* renderer = SDL_CreateRenderer(hwnd.get(), index, flags);
    if (!renderer) {
      throw std::runtime_error("SDL_CreateRenderer has failed: " + std::string(SDL_GetError()));
    }

    HRDR hrdr{ renderer, SDL_DestroyRenderer };
    return hrdr;
  }

  void destroy_renderer(HRDR hrdr) {
    SDL_DestroyRenderer(hrdr.get());
  }

  HTEX create_texture(HRDR hrdr, const char *file) {
    auto p_texture = IMG_LoadTexture(hrdr.get(), "res/icon_16x16.bmp");
    HTEX texture{ p_texture, SDL_DestroyTexture };
    if (!p_texture) {
      std::cerr << "IMG_LoadTexture has failed: " << SDL_GetError() << std::endl;
    }
    return texture;
  }

  uint32_t register_userevent() {
    uint32_t type = SDL_RegisterEvents(1);
    if (type == (uint32_t) - 1) {
      std::cerr << "SDL_RegisterEvents has failed: " << SDL_GetError() << std::endl;
    }
    return type;
  };

  uint32_t get_userevent_type() {
    static uint32_t type = register_userevent();
    return type;
  };

  void trigger_userevent(UserEventCode code, void* data1, void* data2) {
    SDL_Event event;
    SDL_zero(event);
    event.type = get_userevent_type();
    event.user.code = (int)code;
    event.user.data1 = data1;
    event.user.data2 = data2;

    SDL_PushEvent(&event);
  };
}
