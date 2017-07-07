#include "physics.hpp"

using namespace engine;

float Physics::gravity = 1.0;
Physics *Physics::instance = 0;
std::vector<GameObject *> Physics::physicables = {};

Physics *Physics::get_instance(){
  if(!instance){
    instance = new Physics();
  }
  return instance;
}

std::pair<float, float> Physics::calculate_speed(std::pair<float, float> speed){
  std::pair<float, float> new_speed;
  new_speed.first = speed.first;
  new_speed.second = speed.second + gravity;
  return new_speed;
}

std::pair<float, float> Physics::calculate_position(std::pair<float, float> position, std::pair<float, float> speed){
  std::pair<float, float> new_position;
  new_position.first = position.first + speed.first;
  new_position.second = position.second + speed.second;
  return new_position;
}

void Physics::update_speed(GameObject *game_object){
  std::pair<float, float> old_speed = game_object->get_speed();
  std::pair<float, float> new_speed = calculate_speed(old_speed);
  game_object->set_speed(new_speed);
}

void Physics::update_position(GameObject *game_object){
  std::pair<float, float> speed = game_object->get_speed();
  std::pair<float, float> old_position = game_object->get_position();
  std::pair<float, float> new_position = calculate_position(old_position, speed);
  game_object->set_position(new_position);
}

void Physics::act_on(GameObject *game_object){
  update_speed(game_object);
  update_position(game_object);
}

void Physics::add_physicable(GameObject *game_object){
  physicables.push_back(game_object);
}

void Physics::act(){
  for (auto game_object : physicables){
    if(game_object->is_active()){
      act_on(game_object);
    }
  }
}

float Physics::get_gravity(){
  return gravity;
}
