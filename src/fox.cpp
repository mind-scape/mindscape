#include "../include/fox.hpp"

using namespace engine;

void Fox::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;
  Image* moving_right_image = dynamic_cast<Image*>(images[0]);
  Image* moving_left_image = dynamic_cast<Image*>(images[1]);

  if(abs(position.first - 512) <= 50){
    velocity = 10;
  }else if(abs(position.first - 512) > 50 && abs(position.first -512) < 200){
    velocity = 5;
  }else if(abs(position.first - 512) >= 200){
    velocity = -20;
  }

  if(event_name == "JUMP"){
      //state == "JUMPING";
  }else if(event_name == "CROUCH"){

  }else if(event_name == "MOVE_LEFT" && !GameObject::on_limit_of_level){

    moving_right_image->deactivate();
    moving_left_image->activate();

    animation_count += 1;
    if(animation_count == 7){
      moving_left_image->coordinatesOnTexture.first -= 120;
      position.first += velocity;
      animation_count = 0;
    }
    if(moving_left_image->coordinatesOnTexture.first <= 0) moving_left_image->coordinatesOnTexture.first = 960;

  }else if(event_name == "MOVE_RIGHT" && !GameObject::on_limit_of_level){

    moving_left_image->deactivate();
    moving_right_image->activate();

    animation_count2 +=1;
    if(animation_count2 == 7){
      position.first -= velocity;
      moving_right_image->coordinatesOnTexture.first += 120;
      animation_count2 = 0;
    }
    if(moving_right_image->coordinatesOnTexture.first >= 1080) moving_right_image->coordinatesOnTexture.first = 0;
  }
}

void Fox::update(){}
