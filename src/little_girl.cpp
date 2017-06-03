#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include <typeinfo>

using namespace engine;


void LittleGirl::on_collision(GameObject* other, Hitbox* p_my_hitbox, Hitbox* p_other_hitbox){
  Platform* p = dynamic_cast<Platform *>(other);
  Hitbox* my_hitbox = dynamic_cast<Hitbox *>(p_my_hitbox);
  Hitbox* other_hitbox = dynamic_cast<Hitbox *>(p_other_hitbox);
  if(y_state == "FALLING" && p){
    for(int i=0 ; i<5; i++)std::cout << "AEGO" << std::endl;
    y_state = "GROUND";
  }else{
    for(int i=0 ; i<5; i++)std::cout << "PAROU DE COLIDIR" << std::endl;
    // y_state = "FALLING";
  }
}


void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  Image* moving_left_image = dynamic_cast<Image*>(images[1]);
  Image* moving_right_image = dynamic_cast<Image*>(images[0]);

  //Verifying if its on the ground
  if(event_name == "JUMP"){
    y_state = "JUMPING";
  }else if(event_name == "CROUCH"){

  }else if(event_name == "MOVE_LEFT"){
    x_state = "RUNNING_LEFT";

    moving_right_image->deactivate();
    moving_left_image->activate();

    animation_count2 +=1;
    if(animation_count2 == 5){
      moving_left_image->coordinatesOnTexture.first -= 192;
      animation_count2 = 0;
    }
    if(moving_left_image->coordinatesOnTexture.first <= 0)
      moving_left_image->coordinatesOnTexture.first = 1536;

  }else if(event_name == "MOVE_RIGHT"){
    x_state = "RUNNING_RIGHT";

    moving_left_image->deactivate();
    moving_right_image->activate();

    animation_count +=1;
    if(animation_count == 5){
      moving_right_image->coordinatesOnTexture.first += 192;
      animation_count = 0;
    }

    if(moving_right_image->coordinatesOnTexture.first >= 1728)
      moving_right_image->coordinatesOnTexture.first = 0;

  }

  //Jumping
  if(y_state == "JUMPING" && position.second >= 35){
    position.second -= 10;
  }else if(y_state != "GROUND"){
    y_state = "FALLING";
  }

  //Falling
  if(y_state == "FALLING" && position.second < 335){
    position.second += 10;
  }

  //Stopping
  if(game_event.state == engine::KeyboardEvent::State::RELEASED){
    x_state = "STOPPED";
  }
}

void LittleGirl::update(){}
