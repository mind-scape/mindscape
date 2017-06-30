#include "../include/background.hpp"

using namespace mindscape;

void Background::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;
  engine::Image* ref0 = dynamic_cast<engine::Image*>(images[0]);
  if(event_name == "MOVE_LEFT"){
    ref0->coordinatesOnTexture.first -= paralax;

    if(ref0->coordinatesOnTexture.first < 0){
      ref0->coordinatesOnTexture.first = 0;
      engine::GameObject::on_limit_of_level = true;
    } else {
      engine::GameObject::on_limit_of_level = false;
    }

  }else if(event_name == "MOVE_RIGHT"){
    ref0->coordinatesOnTexture.first += paralax;

    if(ref0->coordinatesOnTexture.first > 1728){
      ref0->coordinatesOnTexture.first = 1728;
      engine::GameObject::on_limit_of_level = true;
    } else {
      engine::GameObject::on_limit_of_level = false;
    }
  }
}

void Background::set_paralax(int p_paralax){
  if(p_paralax > 10 || p_paralax < 0)
    paralax = 10;
  else
    paralax = p_paralax;
}


int Background::get_paralax(){
  return paralax;
}
