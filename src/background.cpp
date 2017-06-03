#include "../include/background.hpp"

using namespace engine;

void Background::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;
  Image* ref0 = dynamic_cast<Image*>(images[0]);

  if(event_name == "MOVE_LEFT"){
    ref0->coordinatesOnTexture.first -= paralax;

    if(ref0->coordinatesOnTexture.first < 0){
      ref0->coordinatesOnTexture.first = 0;
      GameObject::on_limit_of_level = true;
    } else {
      GameObject::on_limit_of_level = false;
    }

  }else if(event_name == "MOVE_RIGHT"){
    ref0->coordinatesOnTexture.first += paralax;

    if(ref0->coordinatesOnTexture.first > 1728){
      ref0->coordinatesOnTexture.first = 1728;
      GameObject::on_limit_of_level = true;
    } else {
      GameObject::on_limit_of_level = false;
    }
  }
}

void Background::update(){}
