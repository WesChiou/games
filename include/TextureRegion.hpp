#ifndef _INCLUDE_TEXTUREREGION_HPP_
#define _INCLUDE_TEXTUREREGION_HPP_

#include <iostream>

#include "alias.hpp"

class TextureRegion {
public:
  TextureRegion() {};

  TextureRegion(HTEX htex) : htex(htex) {
    int w, h;
    if (SDL_QueryTexture(htex.get(), nullptr, nullptr, &w, &h) == 0) {
      region = { 0, 0, w, h };
    }
  };

  TextureRegion(HTEX htex, Rect region) : htex(htex), region(region) {};

  HTEX htex{ nullptr };
  Rect region{ 0, 0, 0, 0 }; // pick a rectangle region in texture
};

#endif
