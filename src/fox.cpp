#include "../include/fox.hpp"

using namespace mindscape;

void Fox::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;
  engine::Image* moving_right_image = dynamic_cast<engine::Image*>(images[0]);
  engine::Image* moving_left_image = dynamic_cast<engine::Image*>(images[1]);
  
  Animation* actual_animation = get_actual_animation();
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");

  if(abs(get_position().first - 512) <= 50){
    velocity = 10;
  }else if(abs(get_position().first - 512) > 50 && abs(get_position().first -512) < 200){
    velocity = 5;
  }else if(abs(get_position().first - 512) >= 200){
    velocity = -20;
  }

  if(event_name == "JUMP"){
      //state == "JUMPING";
  }else if(event_name == "CROUCH"){

  }else if(event_name == "MOVE_LEFT" && !engine::GameObject::on_limit_of_level){

    moving_right_image->deactivate();
    moving_left_image->activate();

    running_left_animation_count += 1;
    if(running_left_animation_count == 7){
      moving_left_image->coordinatesOnTexture.first -= 120;
      set_speed(std::make_pair(velocity, get_speed().second));
      running_left_animation_count = 0;
    }
    if(moving_left_image->coordinatesOnTexture.first <= 0) moving_left_image->coordinatesOnTexture.first = 960;

  }else if(event_name == "MOVE_RIGHT" && !engine::GameObject::on_limit_of_level){

    moving_left_image->deactivate();
    moving_right_image->activate();

    running_right_animation_count +=1;
    if(running_right_animation_count == 7){
      set_speed(std::make_pair(-velocity, get_speed().second));
      moving_right_image->coordinatesOnTexture.first += 120;
      running_right_animation_count = 0;
    }
    if(moving_right_image->coordinatesOnTexture.first >= 1080) moving_right_image->coordinatesOnTexture.first = 0;
  }
}

void Fox::update_state(){
  std::string actual_x_state = states.get_state("X_STATE");
  std::string actual_y_state = states.get_state("Y_STATE");
}
