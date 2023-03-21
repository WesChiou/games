#ifndef INCLUDE_RENDERER_HPP_
#define INCLUDE_RENDERER_HPP_

#include "./Scene.hpp"
#include "./Camera.hpp"
#include "./alias.hpp"

class Renderer {
public:
  Renderer() {}
  explicit Renderer(HRDR hrdr) : hrdr(hrdr) {}

  // Set or change SDL_render.
  void set_renderer(HRDR hrdr) { this->hrdr = hrdr; }

  // Using the camera to take a view from the scene,
  // then draw it to the viewport.
  void render(const Scene& scene, const Camera* camera = nullptr, const Rect* viewport = nullptr);

private:
  HRDR hrdr;

  // Recursively render an object and its children.
  void render_object(Object& object, int offset_x, int offset_y);
};

#endif  // INCLUDE_RENDERER_HPP_
