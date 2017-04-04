/*
 * Menu.hpp
 *
 *  Created on: 6 mars 2014
 *      Author: simon
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Common.hpp"

class Menu {
public:
  Menu(const char * fileName);
  virtual ~Menu();

  void display(SDL_Surface* screen);

private:
  SDL_Surface * _image;
  SDL_Rect _menuPos;
};

#endif /* MENU_HPP_ */
