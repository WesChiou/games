#ifndef _INCLUDE_GAMEOBJECT_HPP_
#define _INCLUDE_GAMEOBJECT_HPP_

#include <vector>
#include <cstdint> // uint32_t
#include <atomic> // atomic_uint32_t

#include "EventTarget.hpp"

class GameObject: public EventTarget {
public:
  GameObject()
  : x(0), y(0), height(0), width(0), id_(current_id++) {};
  GameObject(int x, int y, int height, int width)
  : x(x), y(y), height(height), width(width), id_(current_id++) {};

  int x;
  int y;
  int height;
  int width;

  uint32_t id() { return id_; };

private:
  uint32_t id_;
  static std::atomic_uint32_t current_id;
};

#endif
