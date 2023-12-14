#ifndef INCLUDE_RENDERER_HPP_
#define INCLUDE_RENDERER_HPP_

#include "./Scene.hpp"
#include "./alias.hpp"

class Renderer {
public:
  Renderer(HRDR hrdr);

  void render(const Scene* scene, const Camera* camera, const Viewport* viewport);

private:
  HRDR hrdr;
};

#endif  // INCLUDE_RENDERER_HPP_
