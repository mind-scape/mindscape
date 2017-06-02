#include "game_object.hpp"
#include <algorithm>

using namespace engine;

bool GameObject::on_limit_of_level;

bool compare(Component* a, Component* b){
  return a->get_priority() < b->get_priority();
}

void GameObject::add_component(Component* component){
  if(dynamic_cast<Audio *>(component)){
    audios.push_back(component);
  }else if(dynamic_cast<Text *>(component)){
    texts.push_back(component);
    sort(texts.begin(), texts.end(), compare);
  }else if(dynamic_cast<Hitbox *>(component)){
    hitboxes.push_back(dynamic_cast<Hitbox *>(component));
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
    if(image->is_active()){
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

std::vector<Hitbox*> GameObject::get_hitboxes(){
  return hitboxes;
}

void GameObject::collide(GameObject* other){
  if(!this->equals(other))
    this->run_collisions(other);
}

void GameObject::run_collisions(GameObject* other){
  for (auto my_hitbox : hitboxes){
    for (auto other_hitbox : other->get_hitboxes()){
      if(my_hitbox->collides_with(other_hitbox)){
        this->on_collision(other, my_hitbox, other_hitbox);
      }
    }
  }
}

void GameObject::update_hitbox(int x_variation, int y_variation){
  hitbox.x = position.first + x_variation;
  hitbox.y = position.second + y_variation;

  // DO NOT DELETE THIS COMMENT
  // std::cout << name << " - X COMEÇA EM: " << hitbox.x << " VAI ATE: " << hitbox.x + hitbox.w << std::endl;
  // std::cout << name << " - Y COMEÇA EM: " << hitbox.y << " VAI ATE: " << hitbox.y + hitbox.h << std::endl;
}

std::string GameObject::get_state(std::string state_name){
  return states.get_state(state_name);
}
