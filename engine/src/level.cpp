#include "level.hpp"

using namespace engine;

void Level::load(){
  for(auto go : objects){
    std::cout << "Loading " << go->name << std::endl;
    mindscape::Clown* clown = dynamic_cast<mindscape::Clown*>(go);
    
    if(clown) clown->load();
    else go->load();
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
  EventHandler::listeners.clear();
}

void Level::draw(){
  for(auto object : objects){
    if(object->is_active()){
      if(object->name == "clown"){
        mindscape::Clown* clown = dynamic_cast<mindscape::Clown*>(object);
        clown->draw();
        for(auto el : clown->get_boss_parts()){
          for(auto animation : el.second->animations){
            std::cout << "Echo animation"  << std::endl;
            std::cout << "Total sprites "  <<animation.second->total_sprites << std::endl;
            std::cout << "Duration of Animation " << animation.second->duration_of_animation << std::endl;
            std::cout << "Numero de linhas " << animation.second->sprite_lines << std::endl;
            std::cout << "Numero de colunas " << animation.second->sprite_columns << std::endl;
          }
        } 
      }
      else object->draw();
    }
  }
}
