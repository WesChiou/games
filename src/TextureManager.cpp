#include "TextureManager.hpp"

bool TextureManager::load(
  SDL_Renderer* renderer,
  std::string filename,
  std::string id
) {
  SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());

  if (!texture) {
    return false;
  }

  TextureManager::instance().texture_map[id] = texture;

  return true;
}

void TextureManager::draw(
  SDL_Renderer* renderer,
  std::string id,
  SDL_Rect* srcrect,
  SDL_Rect* dstrect
) {
  if (SDL_RenderCopy(renderer
     , TextureManager::instance().texture_map[id]
     , srcrect
     , dstrect
    ) != 0
  ) {
    throw std::runtime_error{ "DrawTexture HAS FAILURE." };
  }
}

void TextureManager::free(std::string id) {
  SDL_DestroyTexture(TextureManager::instance().texture_map[id]);
  TextureManager::instance().texture_map.erase(id);
}

void TextureManager::cleanup() {
  for (auto pair : TextureManager::instance().texture_map) {
    SDL_DestroyTexture(pair.second);
  }
  TextureManager::instance().texture_map.clear();
}
