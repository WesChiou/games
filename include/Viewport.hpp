#ifndef _INCLUDE_VIEWPORT_HPP_
#define _INCLUDE_VIEWPORT_HPP_

#include <cstdint>

#include "engine.hpp"
#include "alias.hpp"

class Viewport {
public:
  Viewport() {};

  Viewport(int x, int y, int w, int h)
  : x(x), y(y), w(w), h(h) {};

  void set_renderer(HRDR hrdr) {
    this->hrdr = hrdr;
  };

  // The x, y, w, and h can specify a rectangle relative to a window.
  int x{0};
  int y{0};
  int w{0};
  int h{0};

  HRDR get_hrdr() const { return hrdr; };

private:
  HRDR hrdr;
};

#endif
