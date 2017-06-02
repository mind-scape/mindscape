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

void Hitbox::set_coordinates(std::pair<int, int> p_displacement){
  hitbox.x = p_displacement.first;
  hitbox.y = p_displacement.second;
  Component::set_displacement(p_displacement);
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

  other_hitbox_coordinates = other_hitbox->get_displacement();
  other_hitbox_dimensions = other_hitbox->get_displacement();

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
