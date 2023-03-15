#ifndef _INCLUDE_MATERIAL_HPP_
#define _INCLUDE_MATERIAL_HPP_

#include "alias.hpp"
#include "TextureRegion.hpp"

class Material {
public:
  Material() {};
  Material(const Color& color) : color(color) {};
  Material(TextureRegion texture_region) : texture_region(texture_region) {};

  Color color{255, 255, 255, 255};

  SDL_Texture* get_texture() {
    return texture_region.get_texture();
  };

  const Rect& get_region() const {
    return texture_region.get_region();
  };

private:
  TextureRegion texture_region;
};

#endif
