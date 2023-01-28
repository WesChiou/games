#ifndef _INCLUDE_DRAW_HPP_
#define _INCLUDE_DRAW_HPP_

#include <cmath>

#include <SDL2/SDL.h>

#include "Transform.hpp"
#include "IShape.hpp"
#include "Circle.hpp"
#include "ConvexPolygon.hpp"
#include "Physics.hpp"

void draw_circle(SDL_Renderer* renderer, double center_x, double center_y, double radius);

void draw_convexpolygon(SDL_Renderer* renderer, std::vector<Vector2D> vertices);

void draw_coord(SDL_Renderer* renderer, Transform& coord);

void draw_spacetime(SDL_Renderer* renderer, Spacetime& spacetime);

#endif
