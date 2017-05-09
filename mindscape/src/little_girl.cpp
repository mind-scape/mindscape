//TODO LUAN Change X by correct numbers, that represents arrow keys on keyboard_events class

#include "../include/little_girl.hpp"
#include "../include/component.hpp"

using namespace engine;

LittleGirl::translations = {
  {X,"JUMP"},
  {X,"CROUCH"},
  {X,"MOVE_LEFT"},
  {X,"MOVE_RIGHT"},
};

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
  }}

/*
void LittleGirl::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component->type].push_back(&component);
}
*/

void LittleGirl::update(){
  
}

