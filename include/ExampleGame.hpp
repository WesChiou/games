#ifndef INCLUDE_EXAMPLEGAME_HPP_
#define INCLUDE_EXAMPLEGAME_HPP_

class ExampleGame {
public:
  void update() {
    msg++;
    if (msg > 99) {
      msg = 0;
    }
  }

  int get_msg() {
    return msg;
  }

private:
  int msg{ 0 };
};

#endif  // INCLUDE_EXAMPLEGAME_HPP_
