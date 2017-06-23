#include "../include/state_map.hpp"

using namespace engine;

void StateMap::set_state (std::string state_name, std::string state_value){
  states[state_name] =  state_value;
}

std::string StateMap::get_state (std::string state_name){
  return states[state_name];
}
