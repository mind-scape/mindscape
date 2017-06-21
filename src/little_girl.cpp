#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include <typeinfo>
#include <algorithm>

using namespace engine;

void LittleGirl::on_collision(GameObject* other, Hitbox* p_my_hitbox, Hitbox* p_other_hitbox){
  Platform* p = dynamic_cast<Platform *>(other);
  Hitbox* my_hitbox = dynamic_cast<Hitbox *>(p_my_hitbox);
  Hitbox* other_hitbox = dynamic_cast<Hitbox *>(p_other_hitbox);

  if(get_speed().second >= 0 && p){ //if she is falling on a platform
    set_speed(std::make_pair(get_speed().first, 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 180));
  }
}

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

 // std::cout << "Position X: " << get_position().first << " Position Y: " << get_position().second << " Speed X: " << get_speed().first << " Speed Y: " << get_speed().second << std::endl;

  Animation* actual_animation = get_actual_animation();

  //Verifying if its on the ground
  //if(event_name == "JUMP" && get_speed().second >= 0){
  if(event_name == "JUMP"){
    set_speed(std::make_pair(get_speed().first, -16));
  }else if(event_name == "MOVE_LEFT"){
    set_speed(std::make_pair(-1.0, get_speed().second));

    set_actual_animation(animations["running_left_animation"]);

    animation_count2 +=1;
    if(animation_count2 == 5){
      actual_animation->coordinatesOnTexture.first -= 192;
      animation_count2 = 0;
    }
    if(actual_animation->coordinatesOnTexture.first <= 0)
      actual_animation->coordinatesOnTexture.first = 1536;
  }else if(event_name == "MOVE_RIGHT"){
    set_speed(std::make_pair(1.0, get_speed().second));

    set_actual_animation(animations["running_right_animation"]);

    animation_count +=1;
    if(animation_count == 5){
      actual_animation->coordinatesOnTexture.first += 192;
      animation_count = 0;
    }

    if(actual_animation->coordinatesOnTexture.first >= 1728)
      actual_animation->coordinatesOnTexture.first = 0;
  }
}

void LittleGirl::update_state(){
  //Should be implemented

  if(get_speed().first == 0.0 && get_speed().second == 0.0){
    if(game_object_direction == "RIGHT"){

    }else if(game_object_direction == "LEFT"){

    }
  }

  std::pair<float,float> new_speed(0.0,get_speed().second);
  set_speed(new_speed);
}
