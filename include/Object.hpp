#ifndef INCLUDE_OBJECT_HPP_
#define INCLUDE_OBJECT_HPP_

#include <vector>
#include <memory>
#include "./alias.hpp"
#include "./Material.hpp"

class Object {
public:
  Object() {}

  Object(int x, int y, int w, int h)
  : x(x), y(y), w(w), h(h) {}

  ~Object() { children.clear(); }

  void add(std::shared_ptr<Object> child) {
    children.emplace_back(child);
  }

  const std::vector<std::shared_ptr<Object>>& get_children() const {
    return children;
  }

  // The x, y, w, and h can specify a rectangle relative to a scene.
  int x{0};
  int y{0};
  int w{0};
  int h{0};

  Material material;

protected:
  std::vector<std::shared_ptr<Object>> children;
};

#endif  // INCLUDE_OBJECT_HPP_
