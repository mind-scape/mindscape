#include "../include/background.hpp"

using namespace engine;

bool Background::load(){
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

void Background::free(){
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

void Background::on_event(GameEvent game_event){

  std::string event_name = game_event.game_event_name;
  Image* ref0 = dynamic_cast<Image*>(images[0]);

  if(event_name == "MOVE_LEFT"){

    ref0->coordinatesOnTexture.first -= 10; 
    std::cout << "Deu " << ref0->coordinatesOnTexture.first << std::endl; 
    if(ref0->coordinatesOnTexture.first <= 0) ref0->coordinatesOnTexture.first = 0;

  }else if(event_name == "MOVE_RIGHT"){

    ref0->coordinatesOnTexture.first += 10; 
    std::cout << "Deu " << ref0->coordinatesOnTexture.first << std::endl; 
    if(ref0->coordinatesOnTexture.first >= 1728) ref0->coordinatesOnTexture.first = 1728;

  }        
}

void Background::update(){
  
}

