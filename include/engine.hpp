#ifndef _INCLUDE_EVENT_HPP_
#define _INCLUDE_EVENT_HPP_

#include <cstdint>

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
  uint32_t register_userevent();
  uint32_t get_registered_type();
  void trigger_userevent(UserEventCode code, void* data1, void* data2);
}

#endif
