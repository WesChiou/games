#include <SDL2/SDL_image.h>
#include <fstream>
#include "../include/nlohmann/json.hpp"
#include "../include/TextureManager.hpp"

using json = nlohmann::json;

TextureManager::TextureManager(HRDR hrdr, std::string texture_region_config): hrdr(hrdr) {
  if (texture_region_config.size()) {
    load_texture_regions(texture_region_config);
  }
}

TextureManager::~TextureManager() {

}

std::optional<TextureRegion> TextureManager::get_texture_region(uint32_t id) {
  if (tr_map.contains(id)) {
    return tr_map[id];
  }
  return std::nullopt;
}

std::optional<HTEX> TextureManager::create_label(std::string text, const FontStyle& font_style) {
  // Ensure font is loaded.
  if (!hfont_map.contains(font_style.source)) {
    TTF_Font* font = TTF_OpenFont(font_style.source.c_str(), font_style.size);
    if (!font) {
      // TODO: logger
      return std::nullopt;
    }
    HFONT hfont { font, TTF_CloseFont };
    hfont_map[font_style.source] = hfont;
  }

  HFONT hfont = hfont_map[font_style.source];

  // Set font style.
  TTF_SetFontOutline(hfont.get(), font_style.outline);
  TTF_SetFontSize(hfont.get(), font_style.size);
  TTF_SetFontStyle(hfont.get(), font_style.style);
  TTF_SetFontWrappedAlign(hfont.get(), font_style.align);

  // Create texture.
  SDL_Surface* surface;;
  switch (font_style.render_mode) {
    case (FontRenderMode::Blended):
      surface = TTF_RenderUTF8_Blended_Wrapped(hfont.get(), text.c_str(), font_style.fg, font_style.wrap_length);
      break;
    case (FontRenderMode::LCD):
      surface = TTF_RenderUTF8_LCD_Wrapped(hfont.get(), text.c_str(), font_style.fg, font_style.bg, font_style.wrap_length);
      break;
    case (FontRenderMode::Shaded):
      surface = TTF_RenderUTF8_Shaded_Wrapped(hfont.get(), text.c_str(), font_style.fg, font_style.bg, font_style.wrap_length);
      break;
    case (FontRenderMode::Solid):
      surface = TTF_RenderUTF8_Solid_Wrapped(hfont.get(), text.c_str(), font_style.fg, font_style.wrap_length);
      break;
    default:
      break;
  }
  if (!surface) {
    // TODO: logger
    return std::nullopt;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(hrdr.get(), surface);
  SDL_FreeSurface(surface);
  if (!texture) {
    // TODO: logger
    return std::nullopt;
  }

  HTEX htex{ texture, SDL_DestroyTexture };

  return htex;
}

std::optional<HTEX> TextureManager::get_htex(std::string file) {
  if (htex_map.contains(file)) {
    return htex_map[file];
  }

  // auto htex = load_texture(file);
  SDL_Texture* texture = IMG_LoadTexture(hrdr.get(), file.c_str());
  if (!texture) {
    // TODO: logger
    return std::nullopt;
  }
  HTEX htex{ texture, SDL_DestroyTexture };

  htex_map[file] = htex;

  return htex;
}

void TextureManager::load_texture_regions(std::string texture_region_config) {
  std::ifstream file(texture_region_config);
  json data = json::parse(file);
  file.close();
  for (auto v : data) {
    auto htex = get_htex(v["file_path"]);
    if (htex.has_value()) {
      tr_map[v["id"]] = {
        .htex = htex.value(),
        .region = SDL_Rect{
          .x = v["srcrect"][0],
          .y = v["srcrect"][1],
          .w = v["srcrect"][2],
          .h = v["srcrect"][3],
        },
      };
    }
  }
}
