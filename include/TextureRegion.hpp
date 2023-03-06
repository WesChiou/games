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

  SDL_Texture* get_texture() { return htex.get(); };

  const Rect& get_region() const { return region; };

  int get_x() const { return region.x; };
  int get_y() const { return region.y; };
  int get_w() const { return region.w; };
  int get_h() const { return region.h; };

  void set_region(Rect new_region) { region = new_region; };

private:
  HTEX htex{};
  Rect region{ 0, 0, 0, 0 }; // pick a rectangle region in texture
};

#endif
