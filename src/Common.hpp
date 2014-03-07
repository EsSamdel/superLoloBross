/*
 * Common.hpp
 *
 *  Created on: 27 févr. 2014
 *      Author: simon
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define PLAYER_MOVE_SPEED 1
#define G 10

enum{
  arret,
  marche,
  saute,
  baisse,
  derape,
  enumEtatLast
};

enum {sky, wall};

struct Rect{
  int x, y;
  int w, h;
};

struct Rect2{
  int x1, y1;
  int x2, y2;
};

struct animUnique{
  int start;
  int length;
  int time;
};

SDL_Surface* loadImage32(const char* fichier_image);
void copyBox(const Rect & boxSrc, Rect & boxCp);

#endif /* COMMON_HPP_ */
