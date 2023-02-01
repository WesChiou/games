#ifndef _INCLUDE_MOUSELISTENER_HPP_
#define _INCLUDE_MOUSELISTENER_HPP_

#include <stack>

#include <SDL2/SDL.h>

class MouseListener {
public:
  static bool init() {
    instance_impl();
    return true;
  };

  static MouseListener& instance() {
    return instance_impl();
  };

  static void cleanup() {};

  void listen(SDL_MouseButtonEvent* e) {
    mouse_events.push(e);
  };

  MouseListener(MouseListener const&) = delete;
  MouseListener& operator = (MouseListener const&) = delete;

private:
  std::stack<SDL_MouseButtonEvent*> mouse_events;

  static MouseListener& instance_impl() {
    static MouseListener instance{};
    return instance;
  };

  MouseListener() {};
};

#endif
