/*
 * Common.cpp
 *
 *  Created on: 27 févr. 2014
 *      Author: simon
 */
#include "Common.hpp"

 SDL_Surface* loadImage32(const char* fichier_image){
  SDL_Surface* image_result;
  SDL_Surface* image_ram = IMG_Load(fichier_image);
  if (image_ram == NULL) {
    std::cout << "Image : " << fichier_image << " introuvable!" << std::endl;
    SDL_Quit();
    exit(-1);
  }
  image_result = SDL_DisplayFormat(image_ram);
  SDL_FreeSurface(image_ram);
  return image_result;
}

 void copyBox(const Rect & boxSrc, Rect & boxCp){
   boxCp.x = boxSrc.x;
   boxCp.y = boxSrc.y;
   boxCp.w = boxSrc.w;
   boxCp.h = boxSrc.h;
 }
