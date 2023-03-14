#ifndef _INCLUDE_CAMERA_HPP_
#define _INCLUDE_CAMERA_HPP_

class Camera {
public:
  Camera() {};

  Camera(int x, int y, int w, int h)
  : x(x), y(y), w(w), h(h) {};

  // The x, y, w, and h can specify a rectangle relative to a scene.
  int x{0};
  int y{0};
  int w{0};
  int h{0};
};

#endif
