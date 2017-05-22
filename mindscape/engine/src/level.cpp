#include "../include/level.hpp"

using namespace engine;

void Level::load(){
  for(auto go : objects){
    std::cout << "Loading " << go.first << std::endl;
    go.second->load();
  }
}

void Level::free(){
  for(auto go : objects){
    std::cout << "Freeing" << go.first << std::endl;
    go.second->free();
  }
}

void Level::draw(){
  for(auto object : objects){
    if(object.second->active_game_object)
      object.second->draw();
  }
}
