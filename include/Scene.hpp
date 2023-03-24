#ifndef INCLUDE_SCENE_HPP_
#define INCLUDE_SCENE_HPP_

#include <vector>
#include <memory>
#include "./Object.hpp"
#include "./alias.hpp"

class Scene {
public:
  Scene() {}
  explicit Scene(HRDR hrdr) : hrdr(hrdr) {}

  void add(std::shared_ptr<Object> child) {
    children.emplace_back(child);
  }

  const std::vector<std::shared_ptr<Object>>& get_children() const {
    return children;
  }

  void update(const Rect* camera = nullptr,
              const Rect* viewport = nullptr,
              bool scale_to_viewport = false);

private:
  std::vector<std::shared_ptr<Object>> children;

  HRDR hrdr;
  Point mouse{0, 0};

  void update_object(Object& object, const Point& offset);
};

#endif  // INCLUDE_SCENE_HPP_
