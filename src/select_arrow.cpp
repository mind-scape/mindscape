
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

  }

  if(event_name == "DOWN"){

  }

}

void SelectArrow::update(){

}