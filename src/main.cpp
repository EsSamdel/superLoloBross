#include "Common.hpp"
#include "Event.hpp"
#include "Menu.hpp"
#include "Game.hpp"

int main() {
  SDL_Surface *screen;

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cout << "Error while init SDL_VIDEO" << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_WM_SetIcon(SDL_LoadBMP("./images/lolo.bmp"), NULL);
  SDL_WM_SetCaption("Super Lolo Bross", NULL);
  screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (screen == NULL) {
    std::cout << "Can't set video mode" << std::endl;
    return EXIT_FAILURE;
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
     std::cout << Mix_GetError() << std::endl;
  }
  Mix_Music *musiqueFond;
  musiqueFond = Mix_LoadMUS("./audio/fond.mp3");
  Mix_PlayMusic(musiqueFond, -1);
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

  Menu menu("./images/menu.jpg");
  Event input;
  while (!input.getKey(SDLK_ESCAPE) && !input.isQuit()) {
    input.UpdateEvents();
    if (input.getKey(SDLK_RETURN)){
      launchGame(screen);
      input.undoKey(SDLK_RETURN);
    }
    menu.display(screen);
    SDL_Flip(screen);
    SDL_Delay(5);
  }

  Mix_FreeMusic(musiqueFond);
  Mix_CloseAudio();
  SDL_Quit();
  return EXIT_SUCCESS;
}
