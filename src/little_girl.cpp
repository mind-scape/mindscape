#include "../include/little_girl.hpp"

using namespace engine;

bool LittleGirl::load(){
    for(auto image : images){
      image.second->load();
    }
    for(auto audio : audios){
      audio->load();
    }
    for(auto text : texts){
      text.second->load();
    }
  return true;
}

void LittleGirl::free(){
  for(auto image : images){
    image.second->free();
  }
  for(auto audio : audios){
    audio->free();
  }
  for(auto text : texts){
    text.second->free();
  }
}

/*
void LittleGirl::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component->type].push_back(&component);
}
*/

void LittleGirl::on_event(GameEvent game_event){
  std::string event_name = game_event.game_event_name;
  Image* ref1 = dynamic_cast<Image*>(images[1].second);
  Image* ref0 = dynamic_cast<Image*>(images[0].second);

  if(event_name == "JUMP"){
//    state == "JUMPING";
  }else if(event_name == "CROUCH"){

  }else if(event_name == "MOVE_LEFT"){

    ref0->active = false;
    ref1->active = true;

    ref1->coordinatesOnTexture.first -= 192;
    if(ref1->coordinatesOnTexture.first <= 0) ref1->coordinatesOnTexture.first = 1536;

  }else if(event_name == "MOVE_RIGHT"){

    ref1->active = false;
    ref0->active = true;

    ref0->coordinatesOnTexture.first += 192;
    if(ref0->coordinatesOnTexture.first >= 1728) ref0->coordinatesOnTexture.first = 0;

  }
}

void LittleGirl::update(){

}
