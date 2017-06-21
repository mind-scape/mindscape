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
  }else if(dynamic_cast<Image *>(component)){
    images.push_back(component);
    sort(images.begin(), images.end(), compare);
  } else {
    animations.push_back(component);
    sort(animations.begin(), animations.end(), compare);
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
  for(auto animation : animations){
    animation->load();
  }
  return true;
}

void GameObject::free(){
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
  for(auto animation : animations){
    animation->draw(position.first, position.second);
  }
  for(auto hitbox : hitboxes){
    if(hitbox -> wanna_draw_hitbox()){
      hitbox->draw();
    }
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

void GameObject::update_hitboxes(){
  for (auto hitbox : hitboxes)
    hitbox->update(position);
}

std::string GameObject::get_state(std::string state_name){
  return states.get_state(state_name);
}

std::pair<float, float> GameObject::get_position(){
  return position;
}

float GameObject::get_position_x(){
  return position.first;
}

float GameObject::get_position_y(){
  return position.second;
}

void GameObject::set_position(std::pair<float, float> p_position){
  position = p_position;
}

void GameObject::set_position_x(float p_x){
  position.first = p_x;
}

void GameObject::set_position_y(float p_y){
  position.second = p_y;
}

std::pair<float, float> GameObject::get_speed(){
  return speed;
}

float GameObject::get_speed_x(){
  return speed.first;
}

float GameObject::get_speed_y(){
  return speed.second;
}

void GameObject::set_speed(std::pair<float, float> p_speed){
  speed = p_speed;
}

void GameObject::set_speed_x(float v_x){
  speed.first = v_x;
}

void GameObject::set_speed_y(float v_y){
  speed.second = v_y;
}

void GameObject::update_state(){
std::cout << "GAME OBJECT UPDATE" << std::endl;
}
