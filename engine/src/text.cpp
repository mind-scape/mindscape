#include "../include/text.hpp"
#include "game.hpp"
#include <string>

using namespace engine;

bool Text::load(){
  font = TTF_OpenFont(font_path.c_str(), font_size);

  SDL_Color sdl_color = {
    color.r,
    color.g,
    color.b,
    color.a
  };

  SDL_Color bg_color = {
    background_color.r,
    background_color.g,
    background_color.b,
    background_color.a
  };

  SDL_Surface * surface = NULL;

  if(bg_color.a == 0x00){
    surface = TTF_RenderText_Blended(
      font,
      text.c_str(),
      sdl_color
    );
  }else{
    surface = TTF_RenderText_Solid(font, text.c_str(), sdl_color);
  }

  if(surface == NULL){
    printf("\nThe text surface cannot be NULL\n");
    return false;
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  if(!texture){
    printf("\nError in the text_texture :%s\n", SDL_GetError());
  }

  if(texture == NULL){
    printf("\n The text_texture cannot be NULL\n");
    return false;
  }

  weigth = surface->w;
  heigth = surface->h;

  activate();
  SDL_FreeSurface(surface);
  return true;
}

void Text::free(){
  SDL_DestroyTexture(texture);
  texture = NULL;

  TTF_CloseFont(font);
  font = NULL;
}

void Text::draw(int x, int y){
  SDL_Rect renderQuad = {x, y, weigth, heigth};
  SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
