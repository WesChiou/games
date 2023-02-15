#ifndef _INCLUDE_HANDLES_HPP_
#define _INCLUDE_HANDLES_HPP_

#include <SDL2/SDL.h>

#include "Handle.hpp"

using WindowHandle = Handle<SDL_Window>;
using RendererHandle = Handle<SDL_Renderer>;

#endif
