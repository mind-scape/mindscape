#include "level.hpp"

using namespace engine;

void Level::load(){
  for(auto game_objects : objects){
    std::cout << "Loading " << game_objects->name << std::endl;
    mindscape::Clown* clown = dynamic_cast<mindscape::Clown*>(game_objects);
    
    if(clown) clown->load();
    else game_objects->load();
    for(auto hit : game_objects->get_hitboxes()){
      hit->initialize();
    }
  }
}

void Level::free(){
  for(auto game_objects : objects){
    std::cout << "Freeing" << game_objects->name << std::endl;
    game_objects->free();
  }
  EventHandler::listeners.clear();
}

void Level::draw(){
  for(auto game_objects : objects){
    if(game_objects->is_active()){
      mindscape::Clown* clown = dynamic_cast<mindscape::Clown*>(game_objects);

      if(clown) clown->draw(); 
      else game_objects->draw();
    }
  }
}
