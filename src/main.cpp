#include "Game.hpp"
#include "StateMinesweeper.hpp"

int main(int argc, char *args[]) {
  Game game;
  StateMinesweeper* state_minesweeper = new StateMinesweeper();

  game.init("Minesweeper");
  game.set_icon("res/icon_16x16.png");
  game.push_state(state_minesweeper);

  game.start();

  return 0;
}
