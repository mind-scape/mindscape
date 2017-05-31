#include "../include/little_girl.hpp"
#include "../include/platform.hpp"
#include <typeinfo>

using namespace engine;

bool LittleGirl::load(){
    for(auto image : images){
      image->load();
    }
    for(auto audio : audios){
      audio->load();
    }
    for(auto text : texts){
      text->load();
    }
  return true;
}

void LittleGirl::free(){
  for(auto image : images){
    image->free();
  }
  for(auto audio : audios){
    audio->free();
  }
  for(auto text : texts){
    text->free();
  }
}

void LittleGirl::on_collision(GameObject* other){
  Platform* p = dynamic_cast<Platform *>(other);
  if(state == "FALLING" && p){
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
    state = "GROUND";
  }
}


void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  Image* moving_left_image = dynamic_cast<Image*>(images[1]);
  Image* moving_right_image = dynamic_cast<Image*>(images[0]);

  //Verifying if its on the ground
  if(event_name == "JUMP" && position.second == 335){
    state = "JUMPING";
  }else if(event_name == "CROUCH"){

  }else if(event_name == "MOVE_LEFT"){
    state = "RUNNING_LEFT";

    moving_right_image->active = false;
    moving_left_image->active = true;

    animation_count2 +=1;
    if(animation_count2 == 7){
      moving_left_image->coordinatesOnTexture.first -= 192;
      animation_count2 = 0;
    }
    if(moving_left_image->coordinatesOnTexture.first <= 0) moving_left_image->coordinatesOnTexture.first = 1536;

  }else if(event_name == "MOVE_RIGHT"){
    state = "RUNNING_RIGHT";

    moving_left_image->active = false;
    moving_right_image->active = true;

    animation_count +=1;
    if(animation_count == 7){
      moving_right_image->coordinatesOnTexture.first += 192;
      animation_count = 0;
    }

    if(moving_right_image->coordinatesOnTexture.first >= 1728) moving_right_image->coordinatesOnTexture.first = 0;

  }

  //Jumping
  if(state == "JUMPING" && position.second >= 35){
    position.second -= 10;
  }else if(state != "GROUND"){
    state = "FALLING";
  }

  //Falling
  if(state == "FALLING" && position.second < 335){
    position.second += 10;
  }

  //Stopping
  if(game_event.state == engine::KeyboardEvent::State::RELEASED){
    state = "STOPPED";
  }

  update_hitbox(60, 130);
}

void LittleGirl::update(){

}
