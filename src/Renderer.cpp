#include <iostream>
#include "../include/Renderer.hpp"

void Renderer::render(const Scene& scene, const Camera* camera,
  const Rect* viewport, bool scale_to_viewport) {
  SDL_Renderer* renderer = hrdr.get();
  if (!renderer) return;

  if (viewport) {
    SDL_RenderSetViewport(renderer, viewport);
  }

  if (scale_to_viewport && camera && viewport) {
    float scale_x = static_cast<float>(viewport->w) / camera->w;
    float scale_y = static_cast<float>(viewport->h) / camera->h;
    SDL_RenderSetScale(renderer, scale_x, scale_y);
  }

  int offset_x{0};
  int offset_y{0};

  if (camera) {
    offset_x = -camera->x;
    offset_y = -camera->y;

    Rect clip_rect{ 0, 0, camera->w, camera->h };
    SDL_RenderSetClipRect(renderer, &clip_rect);
  }

  // Draw objects.
  for (const auto& object : scene.get_children()) {
    render_object(*object, offset_x, offset_y);
  }

  // Reset renderer.
  SDL_RenderSetScale(renderer, 1.0, 1.0);
  SDL_RenderSetClipRect(renderer, nullptr);
  SDL_RenderSetViewport(renderer, nullptr);
}

void Renderer::render_object(Object& object, int offset_x, int offset_y) {
  SDL_Renderer* renderer = hrdr.get();
  if (!renderer) return;

  Rect object_rect{
    .x = object.x + offset_x,
    .y = object.y + offset_y,
    .w = object.w,
    .h = object.h,
  };

  if (object.material.get_texture()) {
    SDL_RenderCopy(renderer, object.material.get_texture(), &object.material.get_region(), &object_rect);
  } else {
    SDL_SetRenderDrawColor(renderer,
      object.material.color.r,
      object.material.color.g,
      object.material.color.b,
      object.material.color.a);
    SDL_RenderFillRect(renderer, &object_rect);
  }

  // Draw children.
  for (const auto& object : object.get_children()) {
    render_object(*object, object_rect.x, object_rect.y);
  }
}
