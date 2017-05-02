#include "../include/level.hpp"

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
