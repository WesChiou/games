#include "Renderer.hpp"

#include <iostream>

void Renderer::render(const Scene& scene, const Camera& camera, const Viewport& viewport) {
  if (!viewport.get_hrdr()) return;

  SDL_Renderer* renderer = viewport.get_hrdr().get();

  Rect camera_rect{
    .x = camera.x,
    .y = camera.y,
    .w = camera.w,
    .h = camera.h,
  };
  Rect clip_rect{ camera_rect };
  SDL_RenderSetClipRect(renderer, &clip_rect);

  Rect viewport_rect{
    .x = viewport.x,
    .y = viewport.y,
    .w = viewport.w,
    .h = viewport.h,
  };
  SDL_RenderSetViewport(renderer, &viewport_rect);

  // Draw objects.
  for (const auto& object : scene.get_children()) {
    Rect object_rect{
      .x = object->x,
      .y = object->y,
      .w = object->w,
      .h = object->h,
    };

    if (object->material.texture_region.get_texture()) {
      SDL_RenderCopy(renderer,
        object->material.texture_region.get_texture(),
        &object->material.texture_region.get_region(),
        &object_rect);
    } else {
      SDL_SetRenderDrawColor(renderer,
        object->material.color.r,
        object->material.color.g,
        object->material.color.b,
        object->material.color.a);
      SDL_RenderFillRect(renderer, &object_rect);
    }
  }

  // Reset clip rect and viewport.
  SDL_RenderSetClipRect(renderer, nullptr);
  SDL_RenderSetViewport(renderer, nullptr);
}
