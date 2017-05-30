
#include "../include/select_arrow.hpp"

using namespace engine;

bool SelectArrow::load(){
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

void SelectArrow::free(){
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


void SelectArrow::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;

  if(event_name == "UP"){
    if(arrow_seletor >= 0 && arrow_seletor < 6){
      arrow_seletor += 1;
    } else {
      arrow_seletor = 0;
    }

  }

  if(event_name == "DOWN"){
    if(arrow_seletor <= 6 && arrow_seletor > 0){
      arrow_seletor -= 1;
    } else {
      arrow_seletor = 6;
    }
  }

  switch(arrow_seletor){
    case(0):
      position.second = 275;
      break;
    case(2):
      position.second = 310;
      break;
    case(4):
      position.second = 345;
      break;
    case(6):
      position.second = 380;
      break;
    default:
      break;
  }

}

void SelectArrow::update(){

}