#ifndef INCLUDE_TEXTUREREGION_HPP_
#define INCLUDE_TEXTUREREGION_HPP_

#include <SDL2/SDL.h>
#include "../include/alias.hpp"

struct TextureRegion {
  HTEX htex{ nullptr };
  SDL_Rect region{ 0, 0, 0, 0 };
};

#endif  // INCLUDE_TEXTUREREGION_HPP_
