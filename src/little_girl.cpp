#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include "../include/game_object_factory.hpp"
#include <typeinfo>
#include <algorithm>

using namespace mindscape;

void LittleGirl::on_collision(
  engine::GameObject* other,
  engine::Hitbox* p_my_hitbox,
  engine::Hitbox* p_other_hitbox){

  engine::Platform* p = dynamic_cast<engine::Platform *>(other);
  engine::Hitbox* my_hitbox = dynamic_cast<engine::Hitbox *>(p_my_hitbox);
  engine::Hitbox* other_hitbox = dynamic_cast<engine::Hitbox *>(p_other_hitbox);

  if(get_speed_y() >= 0 && p){ //if she is falling on a platform
    set_speed_y(0.0);
    set_position_y(other_hitbox->get_coordinates().second - 180);
  }
}

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;
  std::cout << "HP: " << get_hp() << std::endl;
 // std::cout << "Position X: " << get_position().first << " Position Y: " << get_position().second << " Speed X: " << get_speed_x() << " Speed Y: " << get_speed_y() << std::endl;

  engine::Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");

  //Verifying if its on the ground
  //if(event_name == "JUMP" && get_speed_y() >= 0){
  if(event_name == "JUMP" && actual_y_state != "JUMPING"){
    set_speed_y(-21);
    states.set_state("Y_STATE","JUMPING");
    std::string actual_x_state = states.get_state("X_STATE");

    if(actual_x_state == "LOOKING_RIGHT")
      set_actual_animation(animations["jumping_right_animation"]);
    else if(actual_x_state == "LOOKING_LEFT")
      set_actual_animation(animations["jumping_left_animation"]);

    jumping_animation_count += 1;
    if(jumping_animation_count < 26){
      if(jumping_animation_count % 5 == 0){
        actual_animation->coordinatesOnTexture.first += 192;
        if(actual_animation->coordinatesOnTexture.first == 960){
          actual_animation->coordinatesOnTexture.first = 0;
        }
      }
    }else{
      jumping_animation_count = 26;
    }

  }else if(event_name == "MOVE_LEFT"){
    if(actual_y_state == "ON_GROUND"){
      states.set_state("X_STATE","LOOKING_LEFT");
      set_actual_animation(animations["running_left_animation"]);

      set_speed_x(-1.0);

      running_left_animation_count +=1;
      if(true){
        actual_animation->coordinatesOnTexture.first -= 192;
        running_left_animation_count = 0;
      }
      if(actual_animation->coordinatesOnTexture.first <= 0)
        actual_animation->coordinatesOnTexture.first = 1536;
    }else if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_RIGHT"){
      states.set_state("X_STATE","LOOKING_LEFT");
      set_actual_animation(animations["jumping_left_animation"]);
    }

  }else if(event_name == "MOVE_RIGHT"){
    if(actual_y_state == "ON_GROUND"){
      states.set_state("X_STATE","LOOKING_RIGHT");
      set_actual_animation(animations["running_right_animation"]);

      set_speed_x(1.0);

      running_right_animation_count +=1;
      if(true){
        actual_animation->coordinatesOnTexture.first += 192;
        running_right_animation_count = 0;
      }
      if(actual_animation->coordinatesOnTexture.first >= 1728)
        actual_animation->coordinatesOnTexture.first = 0;
    }else if(actual_y_state == "JUMPING" && actual_x_state == "LOOKING_LEFT"){
      states.set_state("X_STATE","LOOKING_RIGHT");
      set_actual_animation(animations["jumping_right_animation"]);
    }
  }
}

void LittleGirl::update_state(){
  //Should be implemented
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");

  if(get_speed_y() == 0.0){
    states.set_state("Y_STATE","ON_GROUND");
  }

  if(get_speed_x() == 0.0 && get_speed_y() == 0.0){
    if(actual_x_state == "LOOKING_RIGHT"){
      engine::Animation* idle_right_animation = animations["idle_right_animation"];
      set_actual_animation(idle_right_animation);
    }else if(actual_x_state == "LOOKING_LEFT"){
      engine::Animation* idle_left_animation = animations["idle_left_animation"];
      set_actual_animation(idle_left_animation);
    }
    jumping_animation_count = 0;
  }

  set_speed_x(0.0);
}
