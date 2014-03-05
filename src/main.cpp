#include "Common.hpp"
#include "Event.hpp"
#include "Level.hpp"
#include "ScrollingBox.hpp"
#include "Perso.hpp"
#include "PhysicalLayer.hpp"

int evolve(Event & input, PhysicalLayer & gameWorld){
  int leftRight = 0;
  int jump = 0;
  int state = arret;
  if (input.getKey(SDLK_LEFT))
    leftRight = -1;
  if (input.getKey(SDLK_RIGHT))
    leftRight = +1;
  if (input.getKey(SDLK_SPACE))
    jump = 1;
  if(leftRight != 0)
    state = marche;

  return gameWorld.persoMove(leftRight, jump, state);

}

int main() {
  SDL_Surface *screen;

  if (SDL_Init(SDL_INIT_VIDEO) == -1){
    std::cout << "Error while init SDL_VIDEO" << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_WM_SetIcon(SDL_LoadBMP("./images/sdl_icone.bmp"), NULL);
  SDL_WM_SetCaption("Super Bro Bross", NULL);
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (screen == NULL) {
    std::cout << "Can't set video mode" << std::endl;
    return EXIT_FAILURE;
  }

  Event input;
  Level levelMap("./level/level.txt");
  Perso perso1("./images/animat.txt", 0, 700, levelMap.getTileSizeX(), 2*levelMap.getTileSizeY());
  ScrollingBox scroll(WINDOW_WIDTH, WINDOW_HEIGHT, 100, 100, 150, 200,
               levelMap.getNbtilesWorldWidth()*levelMap.getTileSizeX(), levelMap.getNbtilesWorldHeight()*levelMap.getTileSizeY(), perso1);
  PhysicalLayer layerGame(&levelMap, &scroll, &perso1);

  int quit = 0;
  int res = 0;
  while(!input.getKey(SDLK_ESCAPE) && !input.isQuit() && !quit)
  {
    input.UpdateEvents();
    res = evolve(input, layerGame);
    if(res == 1 || res == 2)
      quit = 1;
    layerGame.displayMap(screen);
    layerGame.displayPerso(screen);
    SDL_Flip(screen);
    SDL_Delay(2);
  }

  if(res == 2)
    layerGame.winAnnimation(screen);

  SDL_Quit();
  return EXIT_SUCCESS;
}
