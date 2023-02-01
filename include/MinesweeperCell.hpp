#ifndef _INCLUDE_MINESWEEPERCELL_HPP_
#define _INCLUDE_MINESWEEPERCELL_HPP_

#include "MinesweeperMark.hpp"

class MinesweeperCell {
public:
  MinesweeperCell(bool mine): mine(mine) {};

  bool is_mine() {
    return mine;
  };

  bool is_dug() {
    return dug;
  };

  void dig() {
    dug = true;
  };

  int around_mines_num() {
    return around_mines_num_;
  };

  void set_around_mines_num(int v) {
    around_mines_num_ = v;
  };

  MinesweeperMark get_mark() {
    return mark;
  };

  void set_mark(MinesweeperMark mark) {
    this->mark = mark;
  };

private:
  bool mine{false};
  bool dug{false};
  int around_mines_num_{0};
  MinesweeperMark mark{none};
};

#endif
