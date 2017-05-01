#include "../include/scene.hpp"

using namespace engine;

void Scene::add_object(std::string name, engine::GameObject* object){
  objects.insert({name, object});
}

void Scene::render(){
  for(auto hash : Scene::objects){
    engine::GameObject* object = hash.second;
    object->render();
  }
}

void Scene::free(){
  for(auto hash : Scene::objects){
    engine::GameObject* object = hash.second;
    object->free();
  }
}
