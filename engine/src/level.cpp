#include "level.hpp"

using namespace engine;

void Level::load(){
  for(auto game_object : objects){
    std::cout << "Loading " << game_object->name << std::endl;
    mindscape::Clown* clown = dynamic_cast<mindscape::Clown*>(game_object);
    
    if(clown) clown->load();
    else game_object->load();
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
    std::cout << "Game Objecdt " << game_object->name << std::endl;
    if(game_object->is_active()){
      mindscape::Clown* clown = dynamic_cast<mindscape::Clown*>(game_object);

      if(clown) clown->draw(); 
      else game_object->draw();
    }
  }
}
