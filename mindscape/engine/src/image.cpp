#include "image.hpp"
#include <string>

using namespace engine;

bool Image::load(){
  free();

  SDL_Texture* new_texture = NULL;

  SDL_Surface* loaded_surface = IMG_Load( image_path.c_str() );
  if( loaded_surface != NULL ){
    new_texture = SDL_CreateTextureFromSurface( renderer, loaded_surface );
    if(new_texture == NULL){
      printf( "Unable to create texture from %s! SDL Error: %s\n", image_path.c_str(), SDL_GetError() );
    }

    SDL_FreeSurface( loaded_surface );
  }else{
    printf("Unable to load image %s! Image error: %s\n",image_path.c_str(), IMG_GetError() );
  }

  texture = new_texture;
  return texture != NULL;
}

void Image::free(){
  if( texture != NULL){
    SDL_DestroyTexture(texture);
    texture = NULL;
    dimensionOnScreen.first = 0;
    dimensionOnScreen.second = 0;
  }
}

void Image::draw(int x, int y){
  SDL_Rect ret = {coordinatesOnTexture.first,coordinatesOnTexture.second, dimensionOnTexture.first, dimensionOnTexture.second};
  // This render_quad tells where the image will appear in the screen
  SDL_Rect render_quad = {x+displacement.first, y+displacement.second, this->get_width(), this->get_height()};
  SDL_RenderCopy(renderer, texture, &ret, &render_quad);
}

void Image::set_values(std::pair<int, int> _dimensionOnScreen, std::pair<int, int> _dimensionOnTexture, std::pair<int, int> _coordinatesOnTexture){
  dimensionOnScreen = _dimensionOnScreen;
  dimensionOnTexture = _dimensionOnTexture;
  coordinatesOnTexture = _coordinatesOnTexture;
}

int Image::get_width(){
  return dimensionOnScreen.first;
}

int Image::get_height(){
  return dimensionOnScreen.second;
}
