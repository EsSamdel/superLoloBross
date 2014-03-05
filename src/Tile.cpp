#include "Tile.hpp"

Tile::Tile(){
  // TODO Utilisez init car alloc dynamique!
}

Tile::~Tile() {
  // TODO Auto-generated destructor stub
}

void Tile::init(const int sizeX, const int sizeY, const int posX, const int posY, const int type, const int physicalType) {
  _rectangle.w = sizeX;
  _rectangle.h = sizeY;
  _rectangle.x = posX;
  _rectangle.y = posY;
  _type = type;
  switch(physicalType){
  case 0:
    _isWall = false;
    _isObject = false;
    _isEnd = false;
    break;
  case 2:
    _isWall = false;
    _isObject = true;
    _isEnd = false;
    break;
  case 3:
    _isWall = false;
    _isObject = false;
    _isEnd = true;
    break;
  default:
    _isWall = true;
    _isObject = false;
    _isEnd = false;
    break;
  }
}
