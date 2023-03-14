#ifndef _INCLUDE_SCENE_HPP_
#define _INCLUDE_SCENE_HPP_

#include <vector>
#include <memory>
#include "Object.hpp"

class Scene {
public:
  void add(std::unique_ptr<Object> child) {
    children.emplace_back(std::move(child));
  };

  const std::vector<std::unique_ptr<Object>>& get_children() const {
    return children;
  };

private:
  std::vector<std::unique_ptr<Object>> children;
};

#endif
