#ifndef GAME_HPP_
#define GAME_HPP_

#include "Common.hpp"
#include "Event.hpp"
#include "Level.hpp"
#include "ScrollingBox.hpp"
#include "Perso.hpp"
#include "PhysicalLayer.hpp"

int evolve(Event & input, PhysicalLayer & gameLayer);
void launchGame(SDL_Surface* screen);

#endif /* GAME_HPP_ */
