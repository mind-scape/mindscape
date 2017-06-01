#include <string>
#include <iostream>

#include "../include/hitbox.hpp"

using namespace engine;

SDL_Rect Hitbox::get_hitbox(){
  return hitbox;
}

void Hitbox::set_hitbox(std::pair<int, int> xy, std::pair<int, int> widthheight){
    hitbox = {
      .x = xy.first + displacement.first,
      .y = xy.second + displacement.second,
      .w = widthheight.first,
      .h = widthheight.second
    };
}
