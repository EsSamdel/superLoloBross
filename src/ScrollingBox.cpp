/*
 * ScrollingBox.cpp
 *
 *  Created on: 27 févr. 2014
 *      Author: simon
 */

#include "ScrollingBox.hpp"

ScrollingBox::ScrollingBox(int windowSizeX, int windowSizeY, int limitBoxSizeX, int limitBoxSizeY, int distLimitX, int distLimitY, int mapSizeX, int mapSizeY, Perso & pers) {
  _mapSizeX = mapSizeX;
  _mapSizeY = mapSizeY;
  _limitBoxSizeX = limitBoxSizeX;
  _limitBoxSizeY = limitBoxSizeY;
  _distLimitX = distLimitX;
  _distLimitY = distLimitY;

  _window.w = windowSizeX;
  _window.h = windowSizeY;
  _window.x = pers.getCenterX() - limitBoxSizeX / 2 - distLimitX;
  _window.y = pers.getCenterY() + pers.getSizeY()/2 - limitBoxSizeY - distLimitY;
  clampScroll();
}

ScrollingBox::~ScrollingBox() {
  // TODO Auto-generated destructor stub
}

void ScrollingBox::update(Perso & pers){
  int centerX = pers.getCenterX();
  int centerY = pers.getCenterY();
  int xMin, xMax, yMin, yMax;
  xMin = _window.x + _distLimitX;
  yMin = _window.y + _distLimitY;
  xMax = xMin + _limitBoxSizeX;
  yMax = yMin + _limitBoxSizeY;
  if(centerX < xMin)
    _window.x -= (xMin - centerX);
  if(centerY < yMin)
    _window.y -= (yMin - centerY);
  if (centerX > xMax)
    _window.x += (centerX - xMax);
  if (centerY>yMax)
    _window.y += (centerY - yMax);
  clampScroll();
}

void ScrollingBox::clampScroll(){
  if (_window.x < 0)
    _window.x = 0;
  if (_window.y < 0)
    _window.y = 0;
  if (_window.x + _window.w > _mapSizeX)
    _window.x = _mapSizeX - _window.w;
  if (_window.y + _window.h > _mapSizeY)
    _window.y = _mapSizeY - _window.h;
}
