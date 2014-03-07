#include "Event.hpp"

Event::Event() {
  _quit = 0;
  _mouseX = 0;
  _mouseY = 0;
  _mousexrel = 0;
  _mouseyrel = 0;
  memset(_key, 0, sizeof(_key));
  memset(_mouseButtons, 0, sizeof(_mouseButtons));
}

Event::~Event() {
}

void Event::UpdateEvents() {
  SDL_Event event;
  _mouseButtons[SDL_BUTTON_WHEELUP] = 0;
  _mouseButtons[SDL_BUTTON_WHEELDOWN] = 0;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        _key[event.key.keysym.sym] = 1;
        break;
      case SDL_KEYUP:
        _key[event.key.keysym.sym] = 0;
        break;
      case SDL_MOUSEMOTION:
        _mouseX = event.motion.x;
        _mouseY = event.motion.y;
        _mousexrel = event.motion.xrel;
        _mouseyrel = event.motion.yrel;
        break;
      case SDL_MOUSEBUTTONDOWN:
        _mouseButtons[event.button.button] = 1;
        break;
      case SDL_MOUSEBUTTONUP:
        if (event.button.button != SDL_BUTTON_WHEELUP
            && event.button.button != SDL_BUTTON_WHEELDOWN)
          _mouseButtons[event.button.button] = 0;
        break;
      case SDL_QUIT:
        _quit = 1;
        break;
      default:
        break;
    }
  }
}
