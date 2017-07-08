#include <cmath>
#include "../include/animation.hpp"
#include "../include/game.hpp"

using namespace engine;

bool Animation::load(){
  time_of_sprite = (int) std::ceil(double(duration_of_animation)/double(total_sprites));

  aux_time = 0;

  Image::load();
  if(in_loop) time->init_timer();
  return true;
}

void Animation::activate(){
  Component::activate();
  if(!in_loop) time->init_timer();
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
      if(is_a_final_animation){
        deactivate();
        game_object->deactivate();
      }else{
        playing_duration_of_animation = duration_of_animation;
      }
    }
  }
    
  if(time_of_sprite == 0.0){
    time_of_sprite = 1.0;
  }

  actual_sprite = (playing_duration_of_animation / time_of_sprite) + first_sprite;
  actual_line = 0;
  actual_column  = abs(actual_sprite % sprite_columns);
  coordinatesOnTexture.first = sprites_order[actual_column] * dimensionOnTexture.first;
  coordinatesOnTexture.second = actual_line * dimensionOnTexture.second;

  Image::draw(x,y);
}

void Animation::set_sprites_order(int total_sprites, std::string direction){
  if(direction == "LEFT"){
    int reverse_index = total_sprites - 1;
    for(int i = 0;i < total_sprites;++i){
      sprites_order[i] = reverse_index;
      reverse_index--;
    }
  }
  else if(direction == "RIGHT"){
    for(int j = 0;j < total_sprites;++j){
      sprites_order[j] = j;
    }
  }
}

void Animation::set_game_object(GameObject* obj){
  game_object = obj;
}
