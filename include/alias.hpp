#ifndef _INCLUDE_ALIAS_HPP_
#define _INCLUDE_ALIAS_HPP_

#include <memory>

#include <SDL2/SDL.h>

#ifdef USE_SDL_TTF
#include <SDL2/SDL_ttf.h>
#endif

using HWND = std::shared_ptr<SDL_Window>;
using HRDR = std::shared_ptr<SDL_Renderer>;
using HTEX = std::shared_ptr<SDL_Texture>;

#ifdef USE_SDL_TTF
using HFONT = std::shared_ptr<TTF_Font>;
#endif

using Rect = SDL_Rect;
using FRect = SDL_FRect;
using Point = SDL_Point;
using FPoint = SDL_FPoint;
using Color = SDL_Color;

#endif
