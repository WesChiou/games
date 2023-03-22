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

  // Use the camera to capture a view of the scene, and then
  // draw it to the viewport. Set the 'scale_to_viewport' to
  // determine whether to scale the view to fit the viewport.
  // Note that this option is only applicable when both the
  // camera and the viewport are not nullptr.
  void render(const Scene& scene, const Camera* camera = nullptr,
    const Rect* viewport = nullptr, bool scale_to_viewport = false);

private:
  HRDR hrdr;

  // Recursively render an object and its children.
  void render_object(Object& object, int offset_x, int offset_y);
};

#endif  // INCLUDE_RENDERER_HPP_
