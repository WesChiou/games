#ifndef _INCLUDE_ALIAS_HPP_
#define _INCLUDE_ALIAS_HPP_

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using HWND = std::shared_ptr<SDL_Window>;
using HRDR = std::shared_ptr<SDL_Renderer>;
using HTEX = std::shared_ptr<SDL_Texture>;
using HFONT = std::shared_ptr<TTF_Font>;
using Rect = SDL_Rect;
using FRect = SDL_FRect;
using Point = SDL_Point;
using FPoint = SDL_FPoint;
using Color = SDL_Color;

#endif
