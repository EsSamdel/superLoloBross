#include "Level.hpp"

Level::Level(const char * fileName) {
  std::ifstream inFile(fileName);
  if (!inFile)
    std::cout << "Erreur lors de la lecture de : " << fileName << std::endl;

  std::string value;
  inFile >> value; // #tileset
  inFile >> value;
  _tileset = loadImage32(value.c_str());
  inFile >> value;
  std::istringstream (value) >> _nbTilesX;
  inFile >> value;
  std::istringstream (value) >> _nbTilesY;
  _tileSizeX = _tileset->w / _nbTilesX;
  _tileSizeY = _tileset->h / _nbTilesY;

  _tileTable = new Tile[_nbTilesX * _nbTilesY];
  unsigned int iTile = 0;
  for(int j=0; j<_nbTilesY; j++)
    for(int i=0; i<_nbTilesX; i++, iTile++){
      int tmp;
      inFile >> value;
      inFile >> value;
      std::istringstream (value) >> tmp;
      _tileTable[iTile].init(_tileSizeX, _tileSizeY, i*_tileSizeX, j*_tileSizeY, iTile, tmp);
    }

  inFile >> value; // #level
  inFile >> value;
  std::istringstream (value) >> _nbtilesWorldWidth;
  inFile >> value;
  std::istringstream (value) >> _nbtilesWorldHeight;

  _schema = new Uint16*[_nbtilesWorldWidth];
  for(int i=0; i<_nbtilesWorldWidth; i++)
    _schema[i] = new Uint16[_nbtilesWorldHeight];

  for(int j=0; j<_nbtilesWorldHeight ;j++)
    for(int i=0; i<_nbtilesWorldWidth ;i++){
      int tmp;
      inFile >> value;
      std::istringstream (value) >> tmp;
      if (tmp >= _nbTilesX*_nbTilesY){
        std::cout << "level tile hors limite" << std::endl;
        SDL_Quit();
        exit(-1);
      }
      _schema[i][j] = tmp;
    }
  _mapBox.x = 0;
  _mapBox.y = 0;
  _mapBox.w = _nbtilesWorldWidth * _tileSizeX;
  _mapBox.h = _nbtilesWorldHeight * _tileSizeY;
}

Level::~Level() {
  SDL_FreeSurface(_tileset);
  for(int i=0; i<_nbtilesWorldHeight; i++)
    delete[] _schema[i];
  delete[] _schema;
  delete[] _tileTable;
}

void Level::checkObjectif(int i, int j){
  _schema[i][j] = 0;
}
