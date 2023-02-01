#ifndef _INCLUDE_STATEMINESWEEPER_HPP_
#define _INCLUDE_STATEMINESWEEPER_HPP_

#include <map>
#include <string>

#include <SDL2/SDL.h>

#include "State.hpp"
#include "MinesweeperMap.hpp"

class StateMinesweeper: public State {
public:
  bool init();
  void handle_event(SDL_Event* e);
  void update();
  void draw();
  void cleanup();

private:
  MinesweeperMap map{9, 12, 10};

  std::map<std::string, SDL_Rect> tiles{
    { "num_1", { 1, 1, 13, 23 } },
    { "num_2", { 15, 1, 13, 23 } },
    { "num_3", { 29, 1, 13, 23 } },
    { "num_4", { 43, 1, 13, 23 } },
    { "num_5", { 57, 1, 13, 23 } },
    { "num_6", { 71, 1, 13, 23 } },
    { "num_7", { 85, 1, 13, 23 } },
    { "num_8", { 99, 1, 13, 23 } },
    { "num_9", { 113, 1, 13, 23 } },
    { "num_0", { 127, 1, 13, 23 } },
    { "num_none", { 141, 1, 13, 23 } },
    { "num_bg", { 155, 1, 13, 23 } },
    { "face_smile", { 1, 25, 24, 24 } },
    { "face_smile_down", { 26, 25, 24, 24 } },
    { "face_worry", { 51, 25, 24, 24 } },
    { "face_proud", { 76, 25, 24, 24 } },
    { "face_upset", { 101, 25, 24, 24 } },
    { "undug", { 1, 50, 16, 16 } },
    { "dug", { 18, 50, 16, 16 } },
    { "mark_certain", { 35, 50, 16, 16 } },
    { "mark_uncertain", { 52, 50, 16, 16 } },
    { "mark_uncertain_down", { 69, 50, 16, 16 } },
    { "mine", { 86, 50, 16, 16 } },
    { "mine_exploded", { 103, 50, 16, 16 } },
    { "mine_detected", { 120, 50, 16, 16 } },
    { "count_0", { 18, 50, 16, 16 } },
    { "count_1", { 1, 67, 16, 16 } },
    { "count_2", { 18, 67, 16, 16 } },
    { "count_3", { 35, 67, 16, 16 } },
    { "count_4", { 52, 67, 16, 16 } },
    { "count_5", { 69, 67, 16, 16 } },
    { "count_6", { 86, 67, 16, 16 } },
    { "count_7", { 103, 67, 16, 16 } },
    { "count_8", { 120, 67, 16, 16 } },
  };
};

#endif
