#ifndef _INCLUDE_ALIAS_HPP_
#define _INCLUDE_ALIAS_HPP_

#include <memory>

#include <SDL2/SDL.h>

using HWND = std::shared_ptr<SDL_Window>;
using HRDR = std::shared_ptr<SDL_Renderer>;
using HTEX = std::shared_ptr<SDL_Texture>;
using Rect = SDL_Rect;
using FRect = SDL_FRect;
using Point = SDL_Point;
using FPoint = SDL_FPoint;

#endif
