/*
 * ScrollingBox.hpp
 *
 *  Created on: 27 févr. 2014
 *      Author: simon
 */

#ifndef SCROLLINGBOX_HPP_
#define SCROLLINGBOX_HPP_

#include "Common.hpp"
#include "Perso.hpp"

class ScrollingBox {
public:
  ScrollingBox(int windowSizeX, int windowSizeY, int limitBoxSizeX, int limitBoxSizeY, int distLimitX, int distLimitY, int mapSizeX, int mapSizeY, Perso & pers);
  virtual ~ScrollingBox();

  void update(Perso & pers);
  inline Rect getWindow(){return _window;};

protected:
  void clampScroll();

protected:
  Rect _window;
  int _limitBoxSizeX, _limitBoxSizeY;
  int _distLimitX, _distLimitY;
  int _mapSizeX;
  int _mapSizeY;
};

#endif /* SCROLLINGBOX_HPP_ */
