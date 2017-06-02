#include "component.hpp"

using namespace engine;

bool Component::is_active(){
  return active;
}

void Component::activate(){
  activate = true;
}

void Component::deactivate(){
  activate = false;
}

std::pair<int, int> Component::get_coordinates(){
  return coordinates;
}

void Component::set_coordinates(std::pair<int, int> p_coordinates){
  coordinates = p_coordinates;
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
