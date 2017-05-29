#include "game_object.hpp"
#include <algorithm>

using namespace engine;

bool compare(Component* a, Component* b){
  return a->priority < b->priority;
}

void GameObject::add_component(std::string type, Component* component){
  if(type == "audio"){
    audios.push_back(component);
  }else if(type == "text"){
    texts.push_back(component);
    sort(texts.begin(), texts.end(), compare);
  }else{
    images.push_back(component);
    sort(images.begin(), images.end(), compare);
  }
}

bool GameObject::load(){
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
