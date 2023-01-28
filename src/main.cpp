#include <iostream>

#include <SDL2/SDL.h>
#include <math.h>

#include "Vector2D.hpp"
#include "Transform.hpp"
#include "IShape.hpp"
#include "Circle.hpp"
#include "ConvexPolygon.hpp"
#include "Physics.hpp"
#include "draw.hpp"
#include "utils.hpp"

int main(int argv, char** args) {
  // Initial SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init HAS FAILED. ERROR: %s\n", SDL_GetError());
    return 1;
  }

  // Initial window
  SDL_Window* window = SDL_CreateWindow(
    "Vector2D",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    960,
    960,
    0
  );
  if (!window) {
    printf("SDL_CreateWindow HAS FAILED. ERROR: %s\n", SDL_GetError());
    return 1;
  }

  // Initial renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    printf("SDL_CreateRenderer HAS FAILED. ERROR: %s\n", SDL_GetError());
    return 1;
  }

  // Init physics objects

  Body body1 = { 1, 0, 0, 0.5, 1 };
  ConvexPolygon polygon1 = { { 10, 10 }, { 10, -10 }, { -10, -10 }, { -10, 10 } };
  body1.set_shape(polygon1);

  Body body2 = { 1, 0, 0, 1, 0.5 };
  Circle circle1 = { 10 * sqrt(2.0) };
  body2.set_shape(circle1);

  Spacetime spacetime = { 50, 50, 1, 1 };
  spacetime.add_body(&body1);
  spacetime.add_body(&body2);

  // Main loop

  const int update_per_second = 60;
  bool running = true;
  bool pause = false;
  Uint32 lastupdate = 0;

  while (running) {
    // Handle events
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      // } else if (e.type == SDL_KEYUP) {
      //   switch (e.key.keysym.sym) {
      //     case SDLK_TAB:
      //       current_speed_index++;
      //       if (current_speed_index >= 4) {
      //         current_speed_index = 0;
      //       }
      //       break;
      //     default:
      //       break;
      //   }
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_SPACE:
            pause = !pause;
            break;
          default:
            break;
        }
      }
    }

    // Update
    if (!pause) {
      Uint32 current = SDL_GetTicks();
      const Uint32 per_frame_in_ms = 1000 / update_per_second;
      if (current - lastupdate >= per_frame_in_ms) {
        lastupdate = current;
        // update
        spacetime.next_tick();
      }
    }

    // Start draw

    // Erase the last frame in dark
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw stuff
    draw_spacetime(renderer, spacetime);

    // Draw current frame to screen
    SDL_RenderPresent(renderer);
  }

  // Clean up

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
