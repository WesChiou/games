#ifndef INCLUDE_VECTOR2D_HPP_
#define INCLUDE_VECTOR2D_HPP_

#include <cmath>

template <typename T>
class Vector2D {
public:
  T x;
  T y;

  Vector2D& operator += (const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vector2D& operator -= (const Vector2D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  Vector2D& operator *= (const float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

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
  }

  float length() {
    return std::sqrt(x * x + y * y);
  }

  T sqrtlen() {
    return x * x + y * y;
  }

  T dot(const Vector2D& rhs) {
    return x * rhs.x + y * rhs.y;
  }

  Vector2D normalize() {
    float inv_len = 1 / length();
    return { x * inv_len, y * inv_len };
  }
};

template <typename T>
inline Vector2D<T> operator + (Vector2D<T> lhs, const Vector2D<T>& rhs) {
  lhs += rhs;
  return lhs;
}

template <typename T>
inline Vector2D<T> operator - (Vector2D<T> lhs, const Vector2D<T>& rhs) {
  lhs -= rhs;
  return lhs;
}

template <typename T>
inline Vector2D<T> operator * (Vector2D<T> lhs, const float scalar) {
  lhs *= scalar;
  return lhs;
}

// for std::set comparison, etc.
template <typename T>
inline bool operator < (const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  if (lhs.x < rhs.x) return true;
  if (lhs.x > rhs.x) return false;
  if (lhs.y < rhs.y) return true;
  return false;
}

// for std::unordered_set, etc.
template <typename T>
inline bool operator == (const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

#endif  // INCLUDE_VECTOR2D_HPP_
