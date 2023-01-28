#include <cmath>

#include <SDL2/SDL.h>
#include <corecrt.h>

#include "draw.hpp"
#include "Vector2D.hpp"
#include "Transform.hpp"
#include "IShape.hpp"
#include "Circle.hpp"
#include "ConvexPolygon.hpp"
#include "Physics.hpp"

// https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void draw_circle(SDL_Renderer* renderer, double center_x, double center_y, double radius) {
  const int diameter = (int)radius * 2;

  int x = radius - 1;
  int y = 0;
  int tx = 1;
  int ty = 1;
  int error = tx - diameter;

  while (x >= y) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);
    SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
    SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
    SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
    SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
    SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
    SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
    SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);

    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void draw_convexpolygon(SDL_Renderer* renderer, std::vector<Vector2D> vertices) {
  for (size_t i = 0; i < vertices.size(); ++i) {
    Vector2D curr = vertices[i];
    Vector2D next = vertices[(i + 1) % vertices.size()];
    SDL_RenderDrawLine(renderer, curr.x, curr.y, next.x, next.y);
  }
}

void draw_coord(SDL_Renderer* renderer, Transform& coord) {
  if (!renderer) return;

  Vector2D origin = coord.transform(0, 0);
  Vector2D x_end = coord.transform(10000, 0);
  Vector2D y_end = coord.transform(0, 10000);

  SDL_RenderDrawLine(renderer, origin.x, origin.y, x_end.x, x_end.y);
  SDL_RenderDrawLine(renderer, origin.x, origin.y, y_end.x, y_end.y);
};

void draw_spacetime(SDL_Renderer* renderer, Spacetime& spacetime) {
  if (!renderer) return;

  SDL_SetRenderDrawColor(renderer, 88, 88, 88, 255);
  draw_coord(renderer, spacetime.get_space());

  for (auto const& body : spacetime.get_bodies()) {
    Transform trans = { body->get_position().x, body->get_position().y };
    Vector2D position = body->get_position();
    Vector2D pos_projection = spacetime.get_space().transform(position);
    SDL_RenderDrawPoint(renderer, pos_projection.x, pos_projection.y);

    if (ConvexPolygon* cp = dynamic_cast<ConvexPolygon*>(body->get_shape())) {
      std::vector<Vector2D> v;
      for (auto vertex : cp->vertices) {
        Vector2D vertex_projection = trans.transform(vertex);
        v.push_back(spacetime.get_space().transform(vertex_projection));
      }

      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      draw_convexpolygon(renderer, v);
    } else if (Circle* cy = dynamic_cast<Circle*>(body->get_shape())) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      draw_circle(renderer, pos_projection.x, pos_projection.y, cy->radius);
    }
  }
}
