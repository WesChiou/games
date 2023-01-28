#ifndef _INCLUDE_CONVEXPOLYGON_HPP_
#define _INCLUDE_CONVEXPOLYGON_HPP_

#include "Vector2D.hpp"
#include "IShape.hpp"
#include "Projection.hpp"

#include "utils.hpp"

class ConvexPolygon: public IShape {
public:
  std::vector<Vector2D> vertices;
  std::vector<Vector2D> normals;

  ConvexPolygon(std::initializer_list<Vector2D> vertex_list) {
    std::vector<Vector2D> v = { vertex_list };
    deduplicate_keep_order(v);
    if (v.size() >= 3) {
      vertices = v;
      normals = polygon_normals(v);
    }
  };

  ConvexPolygon(std::vector<Vector2D>& vertex_list) {
    std::vector<Vector2D> v(vertex_list.size());
    std::copy(vertex_list.begin(), vertex_list.end(), v.begin());
    deduplicate_keep_order(v);
    if (v.size() >= 3) {
      vertices = v;
      normals = polygon_normals(v);
    }
  };

  ~ConvexPolygon() {};

  virtual ConvexPolygon* clone() const {
    return new ConvexPolygon(*this);
  };

  Projection project(Vector2D& axis) {
    if (vertices.size() < 3) return { 0, 0 };

    double min = axis.dot(vertices[0]);
    double max = min;
    for (auto ver : vertices) {
      double p = axis.dot(ver);
      if (p < min) {
        min = p;
      } else if (p > max) {
        max = p;
      }
    }
    return { min, max };
  };
};

#endif
