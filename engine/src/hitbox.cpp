#include <string>
#include <iostream>

#include "hitbox.hpp"

using namespace engine;


std::pair<int, int> Hitbox::get_dimensions(){
  return std::make_pair(hitbox.w, hitbox.h);
}

void Hitbox::set_dimensions(std::pair<int, int> p_dimensions){
  hitbox.w = p_dimensions.first;
  hitbox.h = p_dimensions.second;
}

void Hitbox::set_displacement(std::pair<int, int> go_coordinates, std::pair<int, int> p_displacement){
  hitbox.x = p_displacement.first + go_coordinates.first;
  hitbox.y = p_displacement.second + go_coordinates.second;
  Component::set_displacement(p_displacement);
}

void Hitbox::update(std::pair<int, int> go_coordinates){
  hitbox.x = get_displacement().first + go_coordinates.first;
  hitbox.y = get_displacement().second + go_coordinates.second;
}

std::pair<int, int> Hitbox::get_coordinates(){
  return std::make_pair(hitbox.x, hitbox.y);
}

bool Hitbox::collides_with(Hitbox* other_hitbox){
  std::pair<int, int> other_hitbox_dimensions;
  std::pair<int, int> other_hitbox_coordinates;
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;
  left_a = hitbox.x;
  right_a = hitbox.x + hitbox.w;
  top_a = hitbox.y;
  bottom_a = hitbox.y + hitbox.h;

  other_hitbox_coordinates = other_hitbox->get_coordinates();
  other_hitbox_dimensions = other_hitbox->get_dimensions();

  left_b = other_hitbox_coordinates.first;     //x
  right_b = other_hitbox_coordinates.first +   //x
            other_hitbox_dimensions.first;     //width
  top_b = other_hitbox_coordinates.second;     //y
  bottom_b = other_hitbox_coordinates.second + //y
             other_hitbox_dimensions.second;   //height

  if(bottom_a <= top_b)
    return false;
  if(top_a >= bottom_b)
    return false;
  if(right_a <= left_b)
    return false;
  if(left_a >= right_b)
    return false;
  return true;
}

void Hitbox::initialize(){
  SDL_Texture* new_texture = NULL;

  SDL_Surface* loaded_surface = IMG_Load("/home/victor/UnB/IJE/mindscape/assets/images/Fundo-Vermelho.jpg");
  if( loaded_surface != NULL ){
    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if(new_texture == NULL){
      printf( "Unable to create texture from! SDL Error: %s\n", SDL_GetError() );
    }
    SDL_FreeSurface(loaded_surface);
  }else{
    printf("Unable to load image");
  }
  texture = new_texture;
}

void Hitbox::draw(){
  SDL_Rect ret = {0, 0, hitbox.w, hitbox.h};
  // This render_quad tells where the image will appear in the screen
  SDL_Rect render_quad = {hitbox.x, hitbox.y, hitbox.w, hitbox.h};
  SDL_RenderCopy(renderer, texture, &ret, &render_quad);
}

bool Hitbox::wanna_draw_hitbox(){
  return draw_hitbox;
}
