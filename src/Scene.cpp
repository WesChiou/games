#include "Scene.hpp"

void Scene::update(const Rect* camera, const Rect* viewport, bool scale_to_viewport) {
  SDL_Renderer* renderer = hrdr.get();

  if (!renderer) return;

  SDL_GetMouseState(&mouse.x, &mouse.y);

  if (viewport) {
    mouse.x -= viewport->x;
    mouse.y -= viewport->y;

    SDL_RenderSetViewport(renderer, viewport);
  }

  if (scale_to_viewport && camera && viewport) {
    float scale_x = static_cast<float>(viewport->w) / camera->w;
    float scale_y = static_cast<float>(viewport->h) / camera->h;

    mouse.x /= scale_x;
    mouse.y /= scale_y;

    SDL_RenderSetScale(renderer, scale_x, scale_y);
  }

  Point offset{0, 0};

  if (camera) {
    offset.x = -camera->x;
    offset.y = -camera->y;

    Rect clip_rect{ 0, 0, camera->w, camera->h };
    SDL_RenderSetClipRect(renderer, &clip_rect);
  }

  for (const auto& object : children) {
    update_object(*object, offset);
  }

  // Reset renderer
  SDL_RenderSetScale(renderer, 1.0, 1.0);
  SDL_RenderSetClipRect(renderer, nullptr);
  SDL_RenderSetViewport(renderer, nullptr);
}

void Scene::update_object(Object& object, const Point& offset) {
  SDL_Renderer* renderer = hrdr.get();

  if (!renderer) return;

  Rect object_rect{
    .x = object.x + offset.x,
    .y = object.y + offset.y,
    .w = object.w,
    .h = object.h,
  };

  Point mouse_point{
    .x = mouse.x,
    .y = mouse.y,
  };

  object.mouseover = mouse.x >= 0
                  && mouse.y >= 0
                  && SDL_PointInRect(&mouse_point, &object_rect);

  if (object.material.get_texture()) {
    SDL_RenderCopy(renderer,
                   object.material.get_texture(),
                   &object.material.get_region(),
                   &object_rect);
  } else {
    SDL_SetRenderDrawColor(renderer,
      object.material.color.r,
      object.material.color.g,
      object.material.color.b,
      object.material.color.a);

    if (object.mouseover) {
      SDL_RenderDrawRect(renderer, &object_rect);
    } else {
      SDL_RenderFillRect(renderer, &object_rect);
    }
  }

  // Update children
  for (const auto& object : object.get_children()) {
    update_object(*object, { object_rect.x, object_rect.y });
  }
}
