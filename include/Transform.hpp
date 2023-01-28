#ifndef _INCLUDE_TRANSFORM_HPP_
#define _INCLUDE_TRANSFORM_HPP_

#include <cmath>

#include "Vector2D.hpp"

class Transform {
public:
  Transform()
  : ox(0.0), oy(0.0), scale_x(1.0), scale_y(1.0), rotate(0.0) {
    set_matrix();
  };
  Transform(double ox, double oy)
  : ox(ox), oy(oy), scale_x(1.0), scale_y(1.0), rotate(0.0) {
    set_matrix();
  };
  Transform(double ox, double oy, double scale_x, double scale_y)
  : ox(ox), oy(oy), scale_x(scale_x), scale_y(scale_y), rotate(0.0) {
    set_matrix();
  };
  Transform(double ox, double oy, double scale_x, double scale_y, double rotate)
  : ox(ox), oy(oy), scale_x(scale_x), scale_y(scale_y), rotate(rotate) {
    set_matrix();
  };

  Vector2D transform(Vector2D& vec) {
    return {
      ox + vec.x * m00 - vec.y * m01,
      oy + vec.y * m10 + vec.x * m11,
    };
  };

  Vector2D transform(double x, double y) {
    return {
      ox + x * m00 - y * m01,
      oy + y * m10 + x * m11,
    };
  };

private:
  double ox;
  double oy;
  double scale_x;
  double scale_y;
  double rotate;

  double m00;
  double m01;
  double m10;
  double m11;

  void set_matrix() {
    double c = cos(rotate);
    double s = sin(rotate);
    m00 = c * scale_x;
    m01 = s * scale_y;
    m10 = c * scale_y;
    m11 = s * scale_x;
  };
};

#endif
