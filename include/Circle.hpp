#ifndef _INCLUDE_CIRCLE_HPP_
#define _INCLUDE_CIRCLE_HPP_

#include <numbers> // numbers::pi

#include "Vector2D.hpp"
#include "IShape.hpp"

class Circle: public IShape {
public:
  double radius;

  Circle(): radius(0.0) {};
  Circle(double radius): radius(radius) {};
  ~Circle() {};

  virtual Circle* clone() const {
    return new Circle(*this);
  };
};

#endif
