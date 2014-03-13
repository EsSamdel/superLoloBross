#include "Game.hpp"

int evolve(Event & input, PhysicalLayer & gameLayer) {
  int leftRight = 0;
  int jump = 0;
  int state = arret;
  if (input.getKey(SDLK_LEFT))
    leftRight = -1;
  if (input.getKey(SDLK_RIGHT))
    leftRight = +1;
  if (input.getKey(SDLK_SPACE))
    jump = 1;
  if (leftRight != 0)
    state = marche;

  return gameLayer.persoMove(leftRight, jump, state);
}

void launchGame(SDL_Surface* screen){
    Event input;
    Level levelMap("./level/level.txt");
    Perso perso1("./images/animat.txt", 0, 700, levelMap.getTileSizeX(), 2 * levelMap.getTileSizeY());
    ScrollingBox scroll(WINDOW_WIDTH, WINDOW_HEIGHT, 100, 100, 150, 200,
        levelMap.getNbtilesWorldWidth() * levelMap.getTileSizeX(),
        levelMap.getNbtilesWorldHeight() * levelMap.getTileSizeY(), perso1);
    PhysicalLayer layerGame(&levelMap, &scroll, &perso1);

    int quit = 0;
    int res = 0;
    int presentTime = 0;
    int previousTime = 0;
    while (!input.getKey(SDLK_ESCAPE) && !input.isQuit() && !quit) {
      presentTime = SDL_GetTicks();
      if (presentTime - previousTime > 4){
        input.UpdateEvents();
        res = evolve(input, layerGame);
        layerGame.displayMap(screen);
        layerGame.displayPerso(screen);
        if (res == 1 || res == 2)
          quit = 1;
        SDL_Flip(screen);
        previousTime = presentTime;
      }
      else{
        SDL_Delay(4 - (presentTime - previousTime));
      }
    }
    if (res == 1)
      layerGame.deathAnnimation(screen);

    if (res == 2)
      layerGame.winAnnimation(screen);

}
