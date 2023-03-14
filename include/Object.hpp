#ifndef _INCLUDE_OBJECT_HPP_
#define _INCLUDE_OBJECT_HPP_

#include <vector>
#include <memory>

#include "alias.hpp"
#include "Material.hpp"

class Object {
public:
  Object() {};

  Object(int x, int y, int w, int h)
  : x(x), y(y), w(w), h(h) {};

  ~Object() { children.clear(); };

  void add(std::unique_ptr<Object> child) {
    children.emplace_back(std::move(child));
  };

  // The x, y, w, and h can specify a rectangle relative to a scene.
  int x{0};
  int y{0};
  int w{0};
  int h{0};

  Material material;

protected:
  std::vector<std::unique_ptr<Object>> children;
};

#endif
