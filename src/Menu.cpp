/*
 * Menu.cpp
 *
 *  Created on: 6 mars 2014
 *      Author: simon
 */

#include "Menu.hpp"

Menu::Menu(const char * fileName) {
  _image = loadImage32(fileName);
  _menuPos.x = 0;
  _menuPos.y = 0;
  _menuPos.w = 0;
  _menuPos.h = 0;
}

Menu::~Menu() {
  // TODO Auto-generated destructor stub
}

void Menu::display(SDL_Surface * screen){
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
  SDL_BlitSurface(_image, NULL, screen, &_menuPos);
}
