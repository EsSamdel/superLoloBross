#ifndef TILE_HPP_
#define TILE_HPP_

#include "Common.hpp"
#include <string>

class Tile {
public:
  Tile();
  virtual ~Tile();
  void init(const int sizeX, const int sizeY, const int posX, const int posY, const int type, const int physicalType);

  inline int getSizeX(){return _rectangle.w;};
  inline int getSizeY(){return _rectangle.h;};
  inline int getPosX(){return _rectangle.x;};
  inline int getPosY(){return _rectangle.y;};
  inline int getType(){return _type;};
  inline bool isWall(){return _isWall;};
  inline bool isObject(){return _isObject;};
  inline bool isEnd(){return _isEnd;};
  inline SDL_Rect * getRectangle(){return &_rectangle;};

protected:
  SDL_Rect _rectangle;
  int _type;
  bool _isWall;
  bool _isObject;
  bool _isEnd;
};

#endif /* TILE_HPP_ */
