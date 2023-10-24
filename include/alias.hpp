#ifndef INCLUDE_ALIAS_HPP_
#define INCLUDE_ALIAS_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

using HWND = std::shared_ptr<SDL_Window>;
using HRDR = std::shared_ptr<SDL_Renderer>;
using HTEX = std::shared_ptr<SDL_Texture>;
using HFONT = std::shared_ptr<TTF_Font>;

#endif  // INCLUDE_ALIAS_HPP_
