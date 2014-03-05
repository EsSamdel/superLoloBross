#include "Perso.hpp"
//#include "Level.hpp"

SDL_Surface* loadImage32(const char* fichier_image);

Perso::Perso(const char * fileName, const int & xPos, const int & yPos, const int & w, const int & h) {
  std::ifstream inFile(fileName);
  if (!inFile)
    std::cout << "Error while reading : " << fileName << std::endl;

  std::string value;
  inFile >> value; // #charset
  inFile >> value;
  _charSet = loadImage32(value.c_str());

  inFile >> value;
  std::istringstream (value) >> _nbCharX;
  inFile >> value;
  std::istringstream (value) >> _nbCharY;
  _persoBox.x = xPos;
  _persoBox.y = yPos;
  _persoBox.w = _charSet->w / _nbCharX;
  _persoBox.h = _charSet->h / _nbCharY;

  int r,g,b;
  inFile >> value;
  std::istringstream (value) >> r;
  inFile >> value;
  std::istringstream (value) >> g;
  inFile >> value;
  std::istringstream (value) >> b;
  SDL_SetColorKey(_charSet, SDL_SRCCOLORKEY, SDL_MapRGB(_charSet->format, r, g, b));

  inFile >> value; // #sequence
  inFile >> value;
  std::istringstream (value) >> _nbDirection;
  inFile >> value;
  std::istringstream (value) >> _nbStates;

  _tabAnim = new animUnique*[_nbDirection];
  for(int i=0; i<_nbDirection; i++){
    _tabAnim[i] = new animUnique[_nbStates];
    for(int j=0; j<_nbStates; j++){
      inFile >> value;
      std::istringstream (value) >> _tabAnim[i][j].start;
      inFile >> value;
      std::istringstream (value) >> _tabAnim[i][j].length;
      inFile >> value;
      std::istringstream (value) >> _tabAnim[i][j].time;
    }
  }
  _sens = 1;
  _state = 0;
  _isInTheAir = 1;
  _wasInTheAir = 1;
  _isOnTheGround = 0;
  _vx = 0;
  _vy = 0;
  _timeStartJump = 0;
  _isJumping = 0;
}

Perso::~Perso() {
  SDL_FreeSurface(_charSet);
  for(int i=0; i<_nbDirection; i++)
    delete[] _tabAnim[i];
  delete[] _tabAnim;
}

void Perso::renderAnimation(SDL_Surface* screen, SDL_Rect* dest){
  int frame;
  SDL_Rect cutCharSet;
  animUnique pa;
  pa = _tabAnim[_sens][_state];
  frame = pa.start + (SDL_GetTicks() / pa.time) % pa.length;
  cutCharSet.x = (frame % _nbCharX) * _persoBox.w;
  cutCharSet.y = (frame / _nbCharX) * _persoBox.h;
  cutCharSet.w = _persoBox.w;
  cutCharSet.h = _persoBox.h;
  SDL_BlitSurface(_charSet, &cutCharSet, screen, dest);
}
