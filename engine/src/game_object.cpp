#include "game_object.hpp"
#include <algorithm>

using namespace engine;

bool GameObject::on_limit_of_level;

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

bool GameObject::equals(GameObject* other){
  return (this == other);
}

void GameObject::collide(GameObject* other){
  if(!this->equals(other) && this->check_collision(other))
    this->on_collision(other);
}

void GameObject::on_collision(GameObject* other){
  std::cout << "BATEU CARAI!" << std::endl;
}

bool GameObject::check_collision(GameObject* other){
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  left_a = hitbox.x;
  right_a = hitbox.x + hitbox.w;
  top_a = hitbox.y;
  bottom_a = hitbox.y + hitbox.h;

  left_b = other->hitbox.x;
  right_b = other->hitbox.x + other->hitbox.w;
  top_b = other->hitbox.y;
  bottom_b = other->hitbox.y + other->hitbox.h;

  if(bottom_a <= top_b)
    return false;
  if(top_a >= bottom_b)
    return false;
  if(right_a <= left_b)
    return false;
  if(left_a >= right_b)
    return false;
  return true;
}
