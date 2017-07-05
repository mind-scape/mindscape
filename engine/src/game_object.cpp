#include "game_object.hpp"
#include "game.hpp"
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
  }
}

void GameObject::add_animation(std::string animation_name, Animation * animation){
  animations[animation_name] = animation;
  animation->set_game_object(this);
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
    animation.second->load();
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
  for(auto animation : animations){
    animation.second->free();
  }
}

void GameObject::draw(){
  for(auto audio : audios){
    audio->draw(position.first, position.second);
  }
  for(auto animation : animations){
    if(animation.second->is_active()){
      animation.second->draw(position.first, position.second);
    }
  }
  for(auto image : images){
    if(image->is_active()){
      image->draw(position.first, position.second);
    }
  }
  for(auto text : texts){
    text->draw(position.first, position.second);
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
      bool my_hitbox_active = my_hitbox->is_active();
      bool other_hitbox_active = other_hitbox->is_active();
      bool should_hitbox_collide = my_hitbox_active && other_hitbox_active;
      if(my_hitbox->collides_with(other_hitbox) && should_hitbox_collide){
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

void GameObject::set_actual_animation(Animation* animation){
  if(actual_animation != NULL) actual_animation->deactivate();
  actual_animation = animation;
  actual_animation->activate();
}

Animation* GameObject::get_actual_animation(){
  return actual_animation;
}

void GameObject::activate(){
  active = true;
}

void GameObject::deactivate(){
  active = false;
}

void GameObject::deactivate_components(){
  for(auto image : images){
    image->deactivate();
  }
  for(auto audio : audios){
    audio->deactivate();
  }
  for(auto text : texts){
    text->deactivate();
  }
  for(auto hitbox : hitboxes){
      hitbox->deactivate();
  }
}

bool GameObject::is_active(){
  return active;
}

void GameObject::update_state(){
//std::cout << "GAME OBJECT UPDATE" << std::endl;
}

int GameObject::get_hp(){
  return hp;
}

void GameObject::set_hp(int health){
  hp = health;
}

void GameObject::create_hitbox(
  std::pair<int, int> displacement,
  std::pair<int, int> dimensions){
  Game& game = Game::get_instance();
  Hitbox* hitbox = new Hitbox("hitbox",
    this->get_position(), displacement, dimensions, game.get_renderer()
  );

  add_component(hitbox);
}

void GameObject::attach_observer(Observer *observer){
  observers.push_back(observer);
}

void GameObject::detach_observer(Observer *observer){
  observers.remove(observer);
}

void GameObject::notify_observers(){
  for(auto observer : observers){
    observer->notify(this);
  }
}
