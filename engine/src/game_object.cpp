#include "game_object.hpp"

using namespace engine;

void GameObject::add_component(std::string type, Component* component){
  if(type == "audio"){
    audios.push_back(component);
  }else if(type == "text"){
    texts.push_back(component);
  }else{
    images.push_back(component);
  }
}

bool GameObject::load(){
  printf("ENTREI NO LOAD\n");
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

void GameObject::draw(){
  for(auto image : images){
    if(image->active){
      image->draw(position.first, position.second);
    }
  }
  for(auto audio : audios){
    audio->draw(position.first, position.second);
  }
  for(auto text : texts){
    text->draw(position.first, position.second);
  }
}
