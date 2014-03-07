#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SDL/SDL.h>

class Event {
public:
  Event();
  virtual ~Event();
  void UpdateEvents();
  inline char& getKey(int i){return _key[i];}
  inline int getMouseX(){return _mouseX;}
  inline int getMouseY(){return _mouseY;}
  inline int getMouseXrel(){return _mousexrel;}
  inline int getMouseYrel(){return _mouseyrel;}
  inline int getMouseButton(int i){return _mouseButtons[i];}
  inline int isQuit(){return _quit;}
  inline void undoKey(int i){_key[i] = 0;};

protected:
  char _key[SDLK_LAST];
  int _mouseX, _mouseY;
  int _mousexrel, _mouseyrel;
  char _mouseButtons[8];
  char _quit;
};

#endif /* EVENT_HPP_ */
