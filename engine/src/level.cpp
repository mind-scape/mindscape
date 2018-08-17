#include "level.hpp"
#include <iostream>

using namespace engine;

void Level::load(){
  for(auto game_object : objects){
    std::cout << "Loading " << game_object->name << std::endl;
    game_object->load();
    for(auto hit : game_object->get_hitboxes()){
      hit->initialize();
    }
  }
}

void Level::free(){
  for(auto game_object : objects){
    std::cout << "Freeing" << game_object->name << std::endl;
    game_object->free();
  }
  EventHandler::listeners.clear();
}

void Level::draw(){
  for(auto game_object : objects){
    if(game_object->is_active()){
      if(game_object->name == "arm_left"){
        game_object->set_actual_animation(game_object->animations["left_arm"]);
      }

      game_object->draw();
    }
  }
}
