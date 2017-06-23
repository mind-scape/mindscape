#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include <typeinfo>
#include <algorithm>

using namespace engine;

void LittleGirl::on_collision(GameObject* other, Hitbox* p_my_hitbox, Hitbox* p_other_hitbox){
  Platform* p = dynamic_cast<Platform *>(other);
  Hitbox* my_hitbox = dynamic_cast<Hitbox *>(p_my_hitbox);
  Hitbox* other_hitbox = dynamic_cast<Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p){ //if she is falling on a platform
    set_speed(std::make_pair(get_speed_x(), 0.0));
    set_position(std::make_pair(get_position().first, other_hitbox->get_coordinates().second - 180));
  }
}

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

 // std::cout << "Position X: " << get_position().first << " Position Y: " << get_position().second << " Speed X: " << get_speed_x() << " Speed Y: " << get_speed_y() << std::endl;

  Animation* actual_animation = get_actual_animation();

  //Verifying if its on the ground
  //if(event_name == "JUMP" && get_speed_y() >= 0){
  if(event_name == "JUMP"){
    set_speed_y(-16);
  }else if(event_name == "MOVE_LEFT"){
    states.set_state("X_STATE","LOOKING_LEFT");
    set_actual_animation(animations["running_left_animation"]);
    
    set_speed_x(-1.0);

    animation_count2 +=1;
    if(animation_count2 == 5){
      actual_animation->coordinatesOnTexture.first -= 192;
      animation_count2 = 0;
    }
    if(actual_animation->coordinatesOnTexture.first <= 0)
      actual_animation->coordinatesOnTexture.first = 1536;
  }else if(event_name == "MOVE_RIGHT"){
    states.set_state("X_STATE","LOOKING_RIGHT");
    set_actual_animation(animations["running_right_animation"]);

    set_speed_x(1.0);

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
  std::string actual_x_state = states.get_state("X_STATE");

  if(get_speed_x() == 0.0 && get_speed_y() == 0.0){
    if(actual_x_state == "LOOKING_RIGHT"){
      Animation* idle_right_animation = animations["idle_right_animation"];
      set_actual_animation(idle_right_animation);
    }else if(actual_x_state == "LOOKING_LEFT"){
      Animation* idle_left_animation = animations["idle_left_animation"];
      set_actual_animation(idle_left_animation);
    }
  }

  set_speed_x(0.0);
}
