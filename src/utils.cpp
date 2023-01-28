#include <vector>
#include <unordered_set> // unordered_set

#include "utils.hpp"
#include "Vector2D.hpp"
#include "Projection.hpp"
#include "IShape.hpp"
#include "Circle.hpp"
#include "ConvexPolygon.hpp"

int deduplicate_keep_order(std::vector<Vector2D>& vec) {
  std::unordered_set<Vector2D, Vector2DHash> seen;

  auto newend = std::remove_if(vec.begin(), vec.end(), [&seen](const Vector2D& value) {
    if (seen.find(value) != std::end(seen)) {
      return true;
    }

    seen.insert(value);
    return false;
  });

  vec.erase(newend, vec.end());

  return vec.size();
}

double polygon_area(std::vector<Vector2D>& vertices) {
  double temp = 0.0;

  for (size_t i = 0; i < vertices.size(); i++) {
    Vector2D curr = vertices[i];
    Vector2D next = vertices[(i + 1) % vertices.size()];
    temp += curr.x * next.y - next.x * curr.y;
  }

  return 0.5 * std::abs(temp);
}

Vector2D polygon_center(std::vector<Vector2D>& vertices) {
  double temp_cx = 0.0;
  double temp_cy = 0.0;
  double area = polygon_area(vertices);

  for (size_t i = 0; i < vertices.size(); i++) {
    Vector2D curr = vertices[i];
    Vector2D next = vertices[(i + 1) % vertices.size()];
    temp_cx += (curr.x + next.x) * (curr.x * next.y - next.x * curr.y);
    temp_cy += (curr.y + next.y) * (curr.x * next.y - next.x * curr.y);
  }

  return { temp_cx / (6 * area), temp_cy / (6 * area) };
}

double polygon_max_circumscribed_circle_radius(std::vector<Vector2D>& vertices, Vector2D& center) {
  double max = 0.0;
  for (auto ver : vertices) {
    Vector2D radius_vec = center - ver;
    double temp = radius_vec.sqrtlen();
    if (temp > max) {
      max = temp;
    }
  }
  return sqrt(max);
}

std::vector<Vector2D> polygon_normals(std::vector<Vector2D>& vertices) {
  std::vector<Vector2D> normals;
  for (size_t i = 0; i < vertices.size(); i++) {
    Vector2D p1 = vertices[i];
    Vector2D p2 = vertices[(i + 1) % vertices.size()];
    Vector2D edge_vec = p1 - p2;
    normals.push_back(edge_vec.perpendicular().normalize());
  }
  deduplicate_keep_order(normals);
  return normals;
};

// ConvexPolygon vs ConvexPolygon
bool intersect(ConvexPolygon& shape1, ConvexPolygon& shape2) {
  // // use max circumscribed circle
  // double r1plusr2 = shape1.get_max_circumscribed_circle_radius() + shape2.get_max_circumscribed_circle_radius();
  // Vector2D c1_to_c2 = shape1.get_center() - shape2.get_center();
  // // more efficient than "r1plusr2 > c1_to_c2.length()", length() use sqrt().
  // if (r1plusr2 * r1plusr2 > c1_to_c2.sqrtlen()) {
  //   return false;
  // }

  // use SAT

  for(auto axis : shape1.normals) {
    Projection p1 = shape1.project(axis);
    Projection p2 = shape2.project(axis);
    if (!p1.overlap(p2)) return false;
  }

  for(auto axis : shape2.normals) {
    Projection p1 = shape1.project(axis);
    Projection p2 = shape2.project(axis);
    if (!p1.overlap(p2)) return false;
  }

  return true;
}

// Circle vs Circle
bool intersect(Circle& shape1, Circle& shape2) {
  // double r1plusr2 = shape1.get_radius() + shape2.get_radius();
  // Vector2D c1_to_c2 = shape1.get_center() - shape2.get_center();

  // if (r1plusr2 * r1plusr2 > c1_to_c2.sqrtlen()) {
  //   return false;
  // }
  return true;
}

// ConvexPolygon vs Circle
bool intersect(ConvexPolygon& shape1, Circle& shape2) {
  // double r1plusr2 = shape1.get_max_circumscribed_circle_radius() + shape2.get_radius();
  // Vector2D c1_to_c2 = shape1.get_center() - shape2.get_center();
  // if (r1plusr2 * r1plusr2 > c1_to_c2.sqrtlen()) {
  //   return false;
  // }
  // TODO: need do more thing to detect.

 return true;
}

// Circle vs ConvexPolygon
bool intersect(Circle& shape1, ConvexPolygon& shape2) {
 return intersect(shape2, shape1);
}

bool intersect(IShape* shape1, IShape* shape2) {
  if (!shape1 || !shape2) return false;

  ConvexPolygon* cp1 = dynamic_cast<ConvexPolygon*>(shape1);
  ConvexPolygon* cp2 = dynamic_cast<ConvexPolygon*>(shape2);
  Circle* cy1 = dynamic_cast<Circle*>(shape1);
  Circle* cy2 = dynamic_cast<Circle*>(shape2);

  if (cp1 && cp2) {
    return intersect(*cp1, *cp2);
  } else if (cp1 && cy2) {
    return intersect(*cp1, *cy2);
  } else if (cy1 && cp2) {
    return intersect(*cy1, *cp2);
  } else if (cy1 && cy2) {
    return intersect(*cy1, *cy2);
  }

  return false;
}
