/*
 * PhysicalLayer.h
 *
 *  Created on: 27 févr. 2014
 *      Author: simon
 */

#ifndef PHYSICALLAYER_H_
#define PHYSICALLAYER_H_

#include "Common.hpp"
#include "LayerInterface.hpp"
#include "Level.hpp"
#include "ScrollingBox.hpp"
#include "Perso.hpp"

class PhysicalLayer: public LayerInterface {
public:
  PhysicalLayer(Level * map, ScrollingBox * scroll, Perso * pers);
  virtual ~PhysicalLayer();

  int persoMove(const int & leftRight, const int & jump, const int & state);
  void displayMap(SDL_Surface* screen);
  void displayPerso(SDL_Surface* screen);
  void winAnnimation(SDL_Surface* screen);

protected:
  Rect2 getAdjacentBox(const Rect & spriteBox);
  Rect2 getFootBox(const Rect & spriteBox);
  Rect2 getHeadBox(const Rect & spriteBox);
  void changePositionPerso(const int & vx, const int & vy);
  void persoJump();
  int testMovePerso(const int & vx, const int & vy);
  void affine(const int & vx, const int & vy);
  int collision(const Rect & spriteBox);
  int isInTheAir(const Rect & spriteBox);
  int isBumpingRoof(const Rect & spriteBox);
  int isOnObjectif(const Rect & spriteBox);
  int isOnEnd(const Rect & spriteBox);
  int isDead(const Rect & spriteBox);

protected:
  Level * _map;
  ScrollingBox * _scroll;
  Perso * _perso;
  int _nbObj;
  int _compteurObj;
};

#endif /* PHYSICALLAYER_H_ */
