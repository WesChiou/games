// Copyright 2023 Qiu Weishi

#include <iostream>
#include <memory>
#include <wish/wish.hpp>
#include "GameMap.hpp"

// void game() {
//   HWND hwnd = engine::create_window("Conway's Game of Life",
//     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//     400, 400, SDL_WINDOW_RESIZABLE);
//   engine::set_window_icon(hwnd, "res/icon_32x32.png");

//   HRDR hrdr = engine::create_renderer(hwnd, -1,
//     SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

//   HTEX ui_texture = engine::create_texture(hrdr, "res/ui_texture.png");
//   TextureRegion texture_dark_pause   {ui_texture, { 0,  0, 16, 16}};
//   TextureRegion texture_gray_pause   {ui_texture, { 0, 16, 16, 16}};
//   TextureRegion texture_dark_play    {ui_texture, {16,  0, 16, 16}};
//   TextureRegion texture_gray_play    {ui_texture, {16, 16, 16, 16}};
//   TextureRegion texture_dark_speedx1 {ui_texture, {32,  0, 16, 16}};
//   TextureRegion texture_gray_speedx1 {ui_texture, {32, 16, 16, 16}};
//   TextureRegion texture_dark_speedx2 {ui_texture, {48,  0, 16, 16}};
//   TextureRegion texture_gray_speedx2 {ui_texture, {48, 16, 16, 16}};

//   auto button_pause   = std::make_shared<Object>(0, 0, 16, 16);
//   auto button_play    = std::make_shared<Object>(16, 0, 16, 16);
//   auto button_speedx1 = std::make_shared<Object>(32, 0, 16, 16);
//   auto button_speedx2 = std::make_shared<Object>(48, 0, 16, 16);

//   button_pause->material = Material{texture_dark_pause};
//   button_play->material = Material{texture_dark_play};
//   button_speedx1->material = Material{texture_dark_speedx1};
//   button_speedx2->material = Material{texture_dark_speedx2};

//   auto control_area = std::make_shared<Object>(0, 0, 64, 16);
//   control_area->add(button_pause);
//   control_area->add(button_play);
//   control_area->add(button_speedx1);
//   control_area->add(button_speedx2);

//   Scene world_ui{hrdr};
//   world_ui.add(control_area);

//   StateOptions menu_options{
//     .pause = false,
//     .invisible = false,
//     .sleep = false,
//   };

//   StateCallbacks menu_callbacks{
//     .on_init = [](StateMachine& sm) {
//       std::cout << "menu init" << std::endl;
//     },

//     .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
//     },

//     .on_update = [](StateMachine& sm) {
//     },

//     .on_draw = [&](StateMachine& sm) {
//     },

//     .on_cleanup = [](StateMachine& sm) {
//       std::cout << "menu cleanup" << std::endl;
//     }
//   };

//   StateOptions world_options{
//     .pause = false,
//     .invisible = false,
//     .sleep = false,
//   };

//   StateCallbacks world_callbacks{
//     .on_init = [](StateMachine& sm) {
//       std::cout << "world init" << std::endl;
//     },

//     .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
//       if (event->type == SDL_USEREVENT) {
//         if (event->user.code == static_cast<int>(engine::UserEventCode::mouse_click)) {
//           std::cout << "clicked" << std::endl;
//         }
//         return;
//       }

//       switch (event->type) {
//         case SDL_KEYDOWN:
//           {
//             switch (event->key.keysym.sym) {
//               case SDLK_UP:
//                 break;
//               case SDLK_RIGHT:
//                 break;
//               case SDLK_DOWN:
//                 break;
//               case SDLK_LEFT:
//                 break;
//               default:
//                 break;
//             }
//           }
//           break;
//         case SDL_KEYUP:
//           {
//             switch (event->key.keysym.sym) {
//               case SDLK_ESCAPE:
//                 std::cout << "show menu" << std::endl;
//                 break;
//               default:
//                 break;
//             }
//           }
//           break;
//         default:
//           break;
//       }
//     },

//     .on_update = [](StateMachine& sm) {
//     },

//     .on_draw = [&](StateMachine& sm) {
//       world_ui.render();
//     },

//     .on_cleanup = [](StateMachine& sm) {
//       std::cout << "world cleanup" << std::endl;
//     }
//   };

//   auto sm = std::make_shared<StateMachine>();

//   auto menu_state = std::make_unique<State>(sm, menu_options, menu_callbacks);
//   sm->push_state("menu", std::move(menu_state));

//   auto world_state = std::make_unique<State>(sm, world_options, world_callbacks);
//   sm->push_state("world", std::move(world_state));

//   sm->start(hrdr);
// }

void game() {
  HWND hwnd = engine::create_window("Conway's Game of Life",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 640, SDL_WINDOW_RESIZABLE);
  engine::set_window_icon(hwnd, "res/icon_32x32.png");

  HRDR hrdr = engine::create_renderer(hwnd, -1,
    SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  GameMap game_map{ 200, 200 };

  StateOptions game_map_state_options{
    .pause = false,
    .invisible = false,
    .sleep = false,
  };

  StateCallbacks game_map_state_callbacks{
    .on_init = [](StateMachine& sm) {
      std::cout << "game map init" << std::endl;
    },

    .on_handle_event = [&](StateMachine& sm, SDL_Event* event) {
      if (event->type == SDL_USEREVENT) {
        if (event->user.code == static_cast<int>(
          engine::UserEventCode::mouse_click)) {
          std::cout << "clicked" << std::endl;
        }
        return;
      }

      switch (event->type) {
        case SDL_KEYDOWN:
          {
            switch (event->key.keysym.sym) {
              case SDLK_TAB:
                game_map.speed_up();
                break;
              case SDLK_SPACE:
                game_map.toggle_pause();
                break;
              default:
                break;
            }
          }
          break;
        default:
          break;
      }
    },

    .on_update = [&](StateMachine& sm) {
      game_map.update();
    },

    .on_draw = [&](StateMachine& sm) {
      game_map.draw_cells(hrdr);
    },

    .on_cleanup = [](StateMachine& sm) {
      std::cout << "game map cleanup" << std::endl;
    }
  };

  auto sm = std::make_shared<StateMachine>();
  auto game_map_state = std::make_shared<State>(sm, game_map_state_options, game_map_state_callbacks);
  sm->push_state("game_map", game_map_state);
  sm->start(hrdr);
}

int main(int argc, char *args[]) {
  if (engine::init(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG)) {
    game();
  }
  engine::quit();

  return 0;
}
