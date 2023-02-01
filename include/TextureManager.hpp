#ifndef _INCLUDE_TEXTUREMANAGER_HPP_
#define _INCLUDE_TEXTUREMANAGER_HPP_

#include <map>
#include <string>
#include <stdexcept> // runtime_error

#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>

class TextureManager {
public:
  static TextureManager& init() {
    return instance_impl();
  };

  static TextureManager& instance() {
    return instance_impl();
  };

  // Load a texture and store it with it's id.
  static bool load(
    SDL_Renderer* renderer,
    std::string filename,
    std::string id
  );

  static void draw(
    SDL_Renderer* renderer,
    std::string id,
    SDL_Rect* srcrect,
    SDL_Rect* dstrect
  );

  // Free single texture by id.
  static void free(std::string id);

  // Cleanup all texture and quit.
  static void cleanup();

  TextureManager(TextureManager const&) = delete;
  TextureManager& operator = (TextureManager const&) = delete;

private:
  std::map<std::string, SDL_Texture*> texture_map;

  static TextureManager& instance_impl() {
    static TextureManager instance{};
    return instance;
  };

  TextureManager() {};
};

#endif
