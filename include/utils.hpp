#ifndef _INCLUDE_UTILS_HPP_
#define _INCLUDE_UTILS_HPP_

#include <vector>
#include <string>

#include "Vector2D.hpp"

class IShape;
class Circle;
class ConvexPolygon;

struct Vector2DHash {
  size_t operator () (const Vector2D& v) const {
    std::string s = std::to_string(v.x) + "," + std::to_string(v.y);
    return std::hash<std::string>{}(s);
  }
};

int deduplicate_keep_order(std::vector<Vector2D>& vec);

double polygon_area(std::vector<Vector2D>& vertices);

Vector2D polygon_center(std::vector<Vector2D>& vertices);

double polygon_max_circumscribed_circle_radius(std::vector<Vector2D>& vertices, Vector2D& center);

std::vector<Vector2D> polygon_normals(std::vector<Vector2D>& vertices);

// ConvexPolygon vs ConvexPolygon
bool intersect(ConvexPolygon& shape1, ConvexPolygon& shape2);

// Circle vs Circle
bool intersect(Circle& shape1, Circle& shape2);

// ConvexPolygon vs Circle
bool intersect(ConvexPolygon& shape1, Circle& shape2);

// Circle vs ConvexPolygon
bool intersect(Circle& shape1, ConvexPolygon& shape2);

bool intersect(IShape* shape1, IShape* shape2);

#endif
