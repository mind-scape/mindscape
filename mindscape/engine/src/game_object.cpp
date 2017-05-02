#include "game_object.hpp"

using namespace engine;

void GameObject::add_component(Component & component){
  std::cout << "Add " << component.type << " to Game Object" << name;
  components[component.type].push_back(&component);
}
