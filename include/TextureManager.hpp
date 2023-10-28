#ifndef INCLUDE_TEXTUREMANAGER_HPP_
#define INCLUDE_TEXTUREMANAGER_HPP_

#include <optional>
#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include "./alias.hpp"
#include "./TextureRegion.hpp"
#include "./FontStyle.hpp"

class TextureManager {
public:
  TextureManager(HRDR hrdr, std::string texture_region_config);
  ~TextureManager();

  std::optional<TextureRegion> get_texture_region(uint32_t id);

  std::optional<HTEX> create_label(std::string text, const FontStyle& font_style);

private:
  HRDR hrdr;

  std::map<std::string, HTEX> htex_map;
  std::map<std::string, HFONT> hfont_map;
  std::map<uint32_t, TextureRegion> texture_region_map;

  std::optional<HTEX> get_htex(std::string file);

  void load_texture_regions(std::string texture_region_config);
};

#endif  // INCLUDE_TEXTUREMANAGER_HPP_
