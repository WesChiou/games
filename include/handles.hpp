#ifndef _INCLUDE_HANDLES_HPP_
#define _INCLUDE_HANDLES_HPP_

#include <memory>

#include <SDL2/SDL.h>

using HWND = std::shared_ptr<SDL_Window>;
using HRDR = std::shared_ptr<SDL_Renderer>;
using HTEX = std::shared_ptr<SDL_Texture>;

#endif
