#include "level.hpp"

using namespace engine;

void Level::load(){
  for(auto go : objects){
    std::cout << "Loading " << go->name << std::endl;
    go->load();
    for(auto hit : go->get_hitboxes()){
      hit->initialize();
    }
  }
}

void Level::free(){
  for(auto go : objects){
    std::cout << "Freeing" << go->name << std::endl;
    go->free();
  }
}

void Level::draw(){
  for(auto object : objects){
    if(object->active_game_object)
      object->draw();
  }
}
