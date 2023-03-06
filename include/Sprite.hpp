#ifndef _INCLUDE_SPRITE_HPP_
#define _INCLUDE_SPRITE_HPP_

#include "TextureRegion.hpp"
#include "alias.hpp"

class Sprite {
public:
  Sprite(TextureRegion tex_rgn)
  : width(tex_rgn.get_w()), height(tex_rgn.get_h()), texture_region(tex_rgn) {};

  Point position{ 0, 0 };
  int width{ 0 };
  int height{ 0 };

  const Rect& get_bounding_box() {
    bounding_box.x = position.x - anchor_point.x * width;
    bounding_box.y = position.y - anchor_point.y * height;
    bounding_box.w = width;
    bounding_box.h = height;
    return bounding_box;
  };

  void set_anchor_point(float anchor_x, float anchor_y) {
    if (anchor_x < 0 || anchor_x > 1 || anchor_y < 0 || anchor_y > 1) {
      return;
    }
    anchor_point.x = anchor_x;
    anchor_point.y = anchor_y;
  };

  void draw(HRDR hrdr, bool show_position = false) {
    if (!hrdr || !texture_region.get_texture()) return;

    SDL_RenderCopy(hrdr.get(), texture_region.get_texture(), &texture_region.get_region(), &get_bounding_box());

    if (show_position) {
      SDL_SetRenderDrawColor(hrdr.get(), 255, 0, 0, 255);
      SDL_RenderDrawPoint(hrdr.get(), position.x, position.y);
    }
  };

private:
  TextureRegion texture_region{};
  Rect bounding_box{ 0, 0, 0, 0 };
  FRect anchor_point{ 0.0, 0.0 };
};

#endif
