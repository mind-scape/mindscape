#include "../include/platform.hpp"

using namespace engine;



bool Platform::load(){
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

void Platform::free(){
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

/*
void Background::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component->type].push_back(&component);
}
*/

void Platform::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;
  Image* ref0 = dynamic_cast<Image*>(images[0]);

  if(event_name == "MOVE_LEFT" && !on_limit_of_level){
    position.first += 10;
  }else if(event_name == "MOVE_RIGHT" && !on_limit_of_level){
    position.first -= 10;
  }
}

void Platform::update(){

}
