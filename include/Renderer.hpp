#ifndef _INCLUDE_RENDERER_HPP_
#define _INCLUDE_RENDERER_HPP_

#include "Scene.hpp"
#include "Camera.hpp"
#include "Viewport.hpp"

class Renderer {
public:
  // Using the camera to take a view from the scene,
  // then draw it to the viewport.
  void render(const Scene& scene, const Camera& camera, const Viewport& viewport);
private:
};

#endif
