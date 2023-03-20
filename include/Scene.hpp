#ifndef INCLUDE_SCENE_HPP_
#define INCLUDE_SCENE_HPP_

#include <vector>
#include <memory>
#include "./Object.hpp"

class Scene {
public:
  void add(std::shared_ptr<Object> child) {
    children.emplace_back(child);
  }

  const std::vector<std::shared_ptr<Object>>& get_children() const {
    return children;
  }

private:
  std::vector<std::shared_ptr<Object>> children;
};

#endif  // INCLUDE_SCENE_HPP_
