#include "component.hpp"

using namespace engine;

bool Component::is_active(){
  return active;
}

void Component::activate(){
  active = true;
}

void Component::deactivate(){
  active = false;
}

std::pair<int, int> Component::get_displacement(){
  return displacement;
}

void Component::set_displacement(std::pair<int, int> p_displacement){
  displacement = p_displacement;
}

int Component::get_priority(){
  return priority;
}

void Component::set_priority(int p_priority){
  priority = p_priority;
}

std::string Component::get_name(){
  return name;
}

void Component::set_name(std::string p_name){
  name = p_name;
}
