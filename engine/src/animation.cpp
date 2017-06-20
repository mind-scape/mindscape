#include <cmath>
#include "../include/animation.hpp"
#include "../include/game.hpp"

using namespace engine;

bool Animation::load(){

    time_of_sprite = (int) std::ceil(double(duration_of_animation) /double(total_sprites));
     std::cout << "total duration " << duration_of_animation << std::endl;
     std::cout << "total colunas  " << sprite_columns << std::endl;
     std::cout << "total linhas  " << sprite_lines << std::endl;
     std::cout << "total sprites  " << total_sprites << std::endl;
     std::cout << "tempo por sprite  " << time_of_sprite << std::endl;

    aux_time = 0;
    is_active = true;

    Image::load();
    time->init_timer();
    return true;
}

void Animation::draw(int x, int y){

      is_finished = false;
      playing_duration_of_animation += time->get_elapsed_time() - aux_time;
      aux_time = time->get_elapsed_time();

      if(playing_duration_of_animation >= duration_of_animation){
        is_finished = true;
        if(in_loop){
          playing_duration_of_animation = playing_duration_of_animation - duration_of_animation;
        } else {
          playing_duration_of_animation = duration_of_animation;
        }
      }

      actual_sprite = (playing_duration_of_animation / time_of_sprite) + first_sprite;

      int actual_line = actual_sprite / sprite_columns;
      int actual_column  = actual_sprite % sprite_columns;

      //Game::get_instance().quit_event = true;

      coordinatesOnTexture.first = sprites_order["left"][actual_column] * dimensionOnTexture.first;
      coordinatesOnTexture.second = actual_line * dimensionOnTexture.second;

    Image::draw(x,y);
}

void Animation::set_sprites_order(int total_sprites){
  int reverse_index = total_sprites - 1;
  for(int i = 0;i < total_sprites;++i){
    sprites_order["left"][i] = reverse_index;
    reverse_index--;    
  }
  
  for(int j = 0;j < total_sprites;++j){
    sprites_order["right"][j] = j;
  } 
}
