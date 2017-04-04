#ifndef PERSO_HPP_
#define PERSO_HPP_

#include "Common.hpp"

class Perso {
public:
  Perso(const char * fileName, const int & xPos, const int & yPos, const int & w, const int & h);
  virtual ~Perso();

  void renderAnimation(SDL_Surface* screen, SDL_Rect* dest);

  inline int getPosX() {return _persoBox.x;}
  inline int getPosY() {return _persoBox.y;}
  inline int getSizeX() {return _persoBox.w;}
  inline int getSizeY() {return _persoBox.h;}
  inline Rect getBox() {return _persoBox;}
  inline int getCenterX() {return _persoBox.x + _persoBox.w/2;}
  inline int getCenterY() {return _persoBox.y + _persoBox.h/2;}
  inline double getSpeedX() {return _vx;};
  inline double getSpeedY() {return _vy;};
  inline int isInTheAir() {return _isInTheAir;};
  inline int wasInTheAir() {return _wasInTheAir;};
  inline int isJumping() {return _isJumping;};

  inline void setBox(Rect box) {_persoBox = box;};
  inline void setState(int state) {_state = state;};
  inline void setSens(int sens) {_sens = sens;};
  inline void setSpeedX(double vx) {_vx = vx;};
  inline void setSpeedY(double vy) {_vy = vy;};
  inline void addSpeedY(double vy) {_vy += vy;};
  inline void setInTheAir(int inOrNot) {_isInTheAir = inOrNot;};
  inline void setWasInTheAir(int inOrNot) {_wasInTheAir = inOrNot;};
  inline void setJump(int isOrNot) {_isJumping = isOrNot;};

protected:
  Rect _persoBox;
  SDL_Surface * _charSet;
  animUnique** _tabAnim;
  int _nbCharX, _nbCharY;
  int _nbDirection;
  int _nbStates;
  int _sens;
  int _state;
  double _vx, _vy;
  int _isOnTheGround;
  int _isInTheAir;
  int _wasInTheAir;
  int _timeStartJump;
  int _isJumping;
};

#endif /* PERSO_HPP_ */
