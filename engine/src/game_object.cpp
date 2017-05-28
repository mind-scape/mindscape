#include "game_object.hpp"
#include <algorithm>

using namespace engine;

bool compare(std::pair<int, Component*> a, std::pair<int, Component*> b){
  return a.first < b.first;
}

void GameObject::add_component(std::string type, Component* component, int priority=10){
  if(type == "audio"){
    audios.push_back(component);
  }else if(type == "text"){
    texts.push_back(std::make_pair(priority, component));
    sort(texts.begin(), texts.end(), compare);
  }else{
    images.push_back(std::make_pair(priority, component));
    sort(images.begin(), images.end(), compare);
  }
}

bool GameObject::load(){
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

void GameObject::draw(){
  for(auto image : images){
    if(image.second->active){
      image.second->draw(position.first, position.second);
    }
  }
  for(auto audio : audios){
    audio->draw(position.first, position.second);
  }
  for(auto text : texts){
    text.second->draw(position.first, position.second);
  }
}
