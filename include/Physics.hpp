#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include <vector>
#include <memory> // unique_ptr
#include <functional> // std::function
#include <atomic> // std::atomic_uint32_t

#include "Vector2D.hpp"
#include "Transform.hpp"
#include "IShape.hpp"

#include "utils.hpp"

class IPhysicsEntity {
public:
  uint32_t get_id() {
    return id;
  };

  IPhysicsEntity(): id(current_id++) {};

  virtual ~IPhysicsEntity() = 0;

protected:
  uint32_t id;
  inline static std::atomic_uint32_t current_id;
};

inline IPhysicsEntity::~IPhysicsEntity() {}

class Body: public IPhysicsEntity {
public:
  Body(): mass(0.0) {};
  Body(double mass): mass(mass) {};
  Body(double mass, double pos_x, double pos_y)
  : mass(mass), position(pos_x, pos_y) {};
  Body(double mass, double pos_x, double pos_y, double vel_x, double vel_y)
  : mass(mass), position(pos_x, pos_y), velocity(vel_x, vel_y) {};
  Body(const Body&) = delete;
  Body& operator = (const Body&) = delete;
  ~Body() = default;

  void update(uint64_t dt = 1) {
    position += velocity * dt;
  };

  double get_mass() {
    return mass;
  };

  Vector2D get_position() {
    return position;
  };

  Vector2D get_velocity() {
    return velocity;
  };

  IShape* get_shape() {
    return shape.get();
  };

  void set_shape(const IShape& shape) {
    this->shape = std::unique_ptr<IShape>(shape.clone());
  };

private:
  double mass;
  Vector2D position;
  Vector2D velocity;
  std::unique_ptr<IShape> shape;
};

class Field: public IPhysicsEntity {
public:
  Field() {};
  Field(const std::function<void (const Body*)>& f): f(f) {};

  void affect(const Body* entity) {
    f(entity);
  };

  virtual ~Field() {};

private:
  std::function<void (const Body*)> f;
};

class ScalarField: public Field {
public:
  double strength;

  ScalarField(): strength(0.0) {};
  ScalarField(const std::function<void (const Body*)>& f): Field(f) {};
  ScalarField(const std::function<void (const Body*)>& f, double strength)
  : Field(f), strength(strength) {};
  ~ScalarField() = default;
};

class Vector2DField: public Field {
public:
  Vector2D strength;

  Vector2DField() {};
  Vector2DField(const std::function<void (const Body*)>& f): Field(f) {};
  Vector2DField(const std::function<void (const Body*)>& f, double x, double y)
  : Field(f), strength(x, y) {};
  ~Vector2DField() = default;
};

inline bool collide(Body& body1, Body& body2) {
  return intersect(body1.get_shape(), body2.get_shape());
}

class Spacetime {
public:
  Spacetime() {};
  Spacetime(double ox, double oy): space(ox, oy) {};
  Spacetime(double ox, double oy, double scale_x, double scale_y)
  : space(ox, oy, scale_x, scale_y) {};
  Spacetime(double ox, double oy, double scale_x, double scale_y, double rotate)
  : space(ox, oy, scale_x, scale_y, rotate) {};

  const std::vector<std::unique_ptr<Body>>& get_bodies() {
    return bodies;
  };

  const std::vector<std::unique_ptr<Field>>& get_fields() {
    return fields;
  };

  Transform& get_space() {
    return space;
  };

  void add_body(Body* body) {
    bodies.push_back(std::unique_ptr<Body>(body));
  };

  bool remove_body(uint32_t id) {
    // TODO
    return true;
  };

  void next_tick() {
    time++;

    // update bodies and fields
    for (auto const& body : bodies) {
      body->update();
    }
    // collision detection
    // solve collision
  };

private:
  Transform space;
  uint64_t time = 0;
  std::vector<std::unique_ptr<Field>> fields;
  std::vector<std::unique_ptr<Body>> bodies;

  void solve_collisions() {
    for (std::size_t i = 0; i < bodies.size(); i++) {
      for (std::size_t j = i + 1; j < bodies.size(); j++) {
        if (collide(*(bodies[i].get()), *(bodies[j].get()))) {
          // TODO: solve collision
        }
      }
    }
  }
};

#endif
