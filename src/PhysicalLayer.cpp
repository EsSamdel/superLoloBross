/*
 * PhysicalLayer.cpp
 *
 *  Created on: 27 févr. 2014
 *      Author: simon
 */

#include "PhysicalLayer.hpp"

PhysicalLayer::PhysicalLayer(Level * map, ScrollingBox * scroll, Perso * pers) {
	_map = map;
	_scroll = scroll;
	_perso = pers;
	_compteurObj = 0;
	_nbObj = 0;
	for(int i = 0; i<_map->getNbtilesWorldWidth(); i++)
	  for(int j = 0; j<_map->getNbtilesWorldHeight() ; j++){
	    int indiceTile = _map->getTileType(i, j);
      if(_map->isTileObject(indiceTile))
        _nbObj += 1;
	  }
}

PhysicalLayer::~PhysicalLayer() {
	// TODO Auto-generated destructor stub
}

int PhysicalLayer::persoMove(const int & leftRight, const int & jump, const int & state){
  int vx;
  vx = leftRight * PLAYER_MOVE_SPEED;

  // set Jump
  int inAir = isInTheAir(_perso->getBox());
  if(inAir)
    _perso->addSpeedY(0.1);
  if(jump && !inAir)
    _perso->setSpeedY(-6);

  changePositionPerso(vx, _perso->getSpeedY());

  // update pour anim :
  if (vx < 0)
    _perso->setSens(0);
  if (vx > 0)
    _perso->setSens(1);
  _perso->setState(state);

  // chech death:
  if(isDead(_perso->getBox()))
    return 1;

  // check objectif:
    if(isOnObjectif(_perso->getBox()))
      _compteurObj += 1;

  // check end:
  int res = isOnEnd(_perso->getBox());
  if(res && _compteurObj == _nbObj)
    return 2;

  return 0;
}

void PhysicalLayer::changePositionPerso(const int & vx, const int & vy){
    int res = testMovePerso(vx, vy);
    if(res == 0)
      affine(vx, vy);
}

void PhysicalLayer::persoJump(){
  if(!isInTheAir(_perso->getBox()))
    _perso->setSpeedY(-6);
}

Rect2 PhysicalLayer::getAdjacentBox(const Rect & spriteBox){
  Rect2 box;
  box.x1 = spriteBox.x / _map->getTileSizeX();
  box.y1 = spriteBox.y / _map->getTileSizeY();
  box.x2 = (spriteBox.x + spriteBox.w -1) / _map->getTileSizeX();
  box.y2 = (spriteBox.y + spriteBox.h -1) / _map->getTileSizeY();
  return box;
}

Rect2 PhysicalLayer::getFootBox(const Rect & spriteBox){ // mal codé!
  Rect2 box;
  box.x1 = spriteBox.x / _map->getTileSizeX();
  box.y1 = (spriteBox.y + spriteBox.h - 1) / _map->getTileSizeY();
  box.x2 = (spriteBox.x + spriteBox.w - 1) / _map->getTileSizeX();
  box.y2 = (spriteBox.y + spriteBox.h - 1) / _map->getTileSizeY();
  return box;
}

int PhysicalLayer::collision(const Rect & spriteBox){
  /*
   * return 1 if collision return 0 else
  */
  Rect2 boxAdjacent = getAdjacentBox(spriteBox);
  if (spriteBox.x < 0 || spriteBox.x + spriteBox.w >= _map->getNbtilesWorldWidth() * _map->getTileSizeX()
     || spriteBox.y < 0 || spriteBox.y + spriteBox.h >= _map->getNbtilesWorldHeight() * _map->getTileSizeY() )
     return 1;

  for(int i = boxAdjacent.x1; i <= boxAdjacent.x2; i++)
    for(int j = boxAdjacent.y1; j <= boxAdjacent.y2; j++){
      int indiceTile = _map->getTileType(i, j);
      if(_map->isTileWall(indiceTile))
        return 1;
    }
  return 0;
}

int PhysicalLayer::isInTheAir(const Rect & spriteBox){
  /*
   * Return 1 if in the air 0 else
   */
  Rect2 foot = getFootBox(spriteBox);
  if((spriteBox.y + spriteBox.h) % _map->getTileSizeY() == 0)
    for(int i = foot.x1; i <= foot.x2; i++){
        int indiceTile = _map->getTileType(i, foot.y1 + 1);
        if(_map->isTileWall(indiceTile))
          return 0;
    }
  return 1;
}

void PhysicalLayer::affine(const int & vx, const int & vy){
  int i;
  for(i=0; i<ABS(vx); i++){
    if (testMovePerso(SGN(vx), 0) == 0)
      break;
  }
  for(i=0; i<ABS(vy); i++){
    if (testMovePerso(0, SGN(vy)) == 0)
      break;
  }
}

int PhysicalLayer::testMovePerso(const int & vx, const int & vy){
  /*
   * return 1 if move return 0 else
   */
  Rect testBox;
  copyBox(_perso->getBox(), testBox);
  testBox.x += vx;
  testBox.y += vy;
  if(collision(testBox) == 0){ // no collision
    _perso->setBox(testBox);
    return 1;
  }
  return 0;
}

int PhysicalLayer::isOnObjectif(const Rect & spriteBox){
  /*
   * return 1 if on return 0 else
  */
  Rect2 boxAdjacent = getAdjacentBox(spriteBox);
  for(int i = boxAdjacent.x1; i <= boxAdjacent.x2; i++)
    for(int j = boxAdjacent.y1; j <= boxAdjacent.y2; j++){
      int indiceTile = _map->getTileType(i, j);
      if(_map->isTileObject(indiceTile)){
        _map->checkObjectif(i, j);
        return 1;
      }
    }
  return 0;
}

int PhysicalLayer::isOnEnd(const Rect & spriteBox){
  /*
   * return 1 if on return 0 else
  */
  Rect2 boxAdjacent = getAdjacentBox(spriteBox);
  for(int i = boxAdjacent.x1; i <= boxAdjacent.x2; i++)
    for(int j = boxAdjacent.y1; j <= boxAdjacent.y2; j++){
      int indiceTile = _map->getTileType(i, j);
      if(_map->isTileEnd(indiceTile))
        return 1;
    }
  return 0;
}

int PhysicalLayer::isDead(const Rect & spriteBox){
  if (spriteBox.y + spriteBox.h +1 >= _map->getNbtilesWorldHeight() * _map->getTileSizeY() )
     return 1;
  return 0;
}

void PhysicalLayer::winAnnimation(SDL_Surface* screen){
  int cpt = 0;
  while(cpt < 10){
    int inAir = isInTheAir(_perso->getBox());
    if(inAir)
      _perso->addSpeedY(0.1);
    if(!inAir){
      _perso->setSpeedY(-6);
      cpt++;
    }
    changePositionPerso(0, _perso->getSpeedY());
    displayMap(screen);
    displayPerso(screen);
    SDL_Flip(screen);
    SDL_Delay(2);
  }
}

void PhysicalLayer::displayPerso(SDL_Surface* screen){
  SDL_Rect copyPerso;
  Rect window = _scroll->getWindow();
  copyPerso.x = _perso->getPosX() - window.x;
  copyPerso.y = _perso->getPosY() - window.y;
  copyPerso.w = _perso->getSizeX();
  copyPerso.h = _perso->getSizeY();
  _perso->renderAnimation(screen, &copyPerso); //moche de faire faire au perso...
}

void PhysicalLayer::displayMap(SDL_Surface* screen){
  SDL_Rect dest;
  int tileNumber;
  int xMin, xMax, yMin, yMax;
  _scroll->update(*_perso);
  Rect window = _scroll->getWindow();
  xMin = window.x / _map->getTileSizeX() - 1;
  xMax = (window.x + window.w) / _map->getTileSizeX();
  yMin = window.y / _map->getTileSizeY() - 1;
  yMax = (window.y + window.h) / _map->getTileSizeY();
  for(int i=xMin; i<xMax+1; i++)
    for(int j=yMin; j<yMax+1; j++){
      dest.x = i * _map->getTileSizeX() - window.x;
      dest.y = j * _map->getTileSizeY() - window.y;
      if ( i<0 || i>= _map->getNbtilesWorldWidth() || j<0 || j>= _map->getNbtilesWorldHeight())
        tileNumber = 0;
      else
        tileNumber = _map->getTileType(i, j);
      SDL_BlitSurface(_map->getTileset(), _map->getTile(tileNumber).getRectangle(), screen, &dest);
    }
}
