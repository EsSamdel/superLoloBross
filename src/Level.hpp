#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "Common.hpp"
#include "Tile.hpp"

class Level {
public:
  Level(const char * fileName);
  virtual ~Level();

  inline int getTileSizeX() {return _tileSizeX;}
  inline int getTileSizeY() {return _tileSizeY;}
  inline int getNbtilesWorldWidth() {return _nbtilesWorldWidth;}
  inline int getNbtilesWorldHeight() {return _nbtilesWorldHeight;}
  inline Uint16 getTileType(const int & i, const int & j){return _schema[i][j];}
  inline bool isTileWall(const int & tileNumber){return _tileTable[tileNumber].isWall();}
  inline bool isTileObject(const int & tileNumber){return _tileTable[tileNumber].isObject();}
  inline bool isTileEnd(const int & tileNumber){return _tileTable[tileNumber].isEnd();}
  inline SDL_Surface * getTileset() {return _tileset;}
  inline Tile getTile(int tileNumber) {return _tileTable[tileNumber];};
  inline Rect getBox() {return _mapBox;};

  void checkObjectif(int i, int j);

protected:
  Rect _mapBox;
  SDL_Surface * screen;
  SDL_Surface * _tileset;
  Tile * _tileTable;
  Uint16** _schema;
  int _nbTilesX, _nbTilesY;
  int _tileSizeX, _tileSizeY;
  int _nbtilesWorldWidth, _nbtilesWorldHeight;
};

#endif /* LEVEL_HPP_ */
