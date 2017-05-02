#include "little_girl.hpp"
#include "component.hpp"

using namespace engine;

bool LittleGirl::load(){
  for(auto component_type : components){
    std::cout << "Loading all components of type " << component_type.first << " in Game Object " << name << "\n";  
  
    for(auto component : component_type.second){
      if(component->load() == false){
        std::cout << "Error while loading component" << "\n";
        return false;
      }
    }    
  }
  
  return true;
}

void LittleGirl::free(){
  for(auto component_type : components){
    std::cout << "Freeing all components of type " << component_type.first << " in Game Object " << name << "\n";  
  
    for(auto component : component_type.second){
      component->free();
    }    
  }
}

/*
void LittleGirl::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component->type].push_back(&component);
} 
*/
