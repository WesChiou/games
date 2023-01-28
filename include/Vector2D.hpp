#ifndef _INCLUDE_VECTOR2D_HPP_
#define _INCLUDE_VECTOR2D_HPP_

#include <cmath> // sqrt, etc.

class Vector2D {
public:
  double x;
  double y;

  Vector2D(): x(0.0), y(0.0) {};
  Vector2D(double x, double y): x(x), y(y) {};

  Vector2D& operator += (const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  };

  Vector2D& operator -= (const Vector2D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  };

  Vector2D& operator *= (const double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  };

  // Get either perpendicular.
  // In general, it doesn't matter if you return { y, -x } or { -y, x },
  // however, when you have two parallel and opposite vectors, you probably
  // want their results to be in the same direction. For example, this
  // method returns { 2, -1 } whether the vector is { 1, 2 } or { -1, -2 }.
  Vector2D perpendicular() {
    if (x >= 0) {
      return { y, x == 0 ? x : -x };
    }
    return { y == 0 ? y : -y, x };
  };

  double length() {
    return std::sqrt(x * x + y * y);
  };

  double sqrtlen() {
    return x * x + y * y;
  };

  double dot(const Vector2D& rhs) {
    return x * rhs.x + y * rhs.y;
  };

  Vector2D normalize() {
    double inv_len = 1 / length();
    return { x * inv_len, y * inv_len };
  };
};

inline Vector2D operator + (Vector2D lhs, const Vector2D& rhs) {
  lhs += rhs;
  return lhs;
}

inline Vector2D operator - (Vector2D lhs, const Vector2D& rhs) {
  lhs -= rhs;
  return lhs;
}

inline Vector2D operator * (Vector2D lhs, const double scalar) {
  lhs *= scalar;
  return lhs;
}

// for std::set comparison, etc.
inline bool operator < (const Vector2D& lhs, const Vector2D& rhs) {
  if (lhs.x < rhs.x) return true;
  if (lhs.x > rhs.x) return false;
  if (lhs.y < rhs.y) return true;
  return false;
}

// for std::unordered_set, etc.
inline bool operator == (const Vector2D& lhs, const Vector2D& rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

#endif
