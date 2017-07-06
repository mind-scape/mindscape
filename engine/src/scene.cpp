#include "scene.hpp"
#include "physics.hpp"
#include <algorithm>

using namespace engine;

bool compare_scene(engine::GameObject* a, GameObject* b){
  return a->priority < b->priority;
}

void Scene::add_object(engine::GameObject* object){
  objects.push_back(object);
  sort(objects.begin(), objects.end(), compare_scene);
}

GameObject *Scene::get_object_by_name(std::string name){
  for (auto game_object : objects)
    if(name == game_object->name)
      return game_object;
  return NULL;
}

void Scene::activate_game_object(GameObject *go){
  go->activate();
  EventHandler::add_listener(go);
}

void Scene::deactivate_game_object(std::string game_object_name){
  int counter = 0;
  for(auto go : objects){
    if(go->name == game_object_name){
      go->deactivate();
      EventHandler::remove_listener(go);
      objects.erase(objects.begin() + counter);
      break;
    }
    counter++;
  }
}

void Scene::deactivate(){
  for(auto go : objects){
      go->deactivate();
  }
  EventHandler::listeners.clear();
}

void Scene::activate(){
  for(auto go : objects)
    activate_game_object(go);
}

void Scene::run_collisions(){
  for(auto go : objects){
    if(go->collidable){
      for(auto another_go : objects){
        go->collide(another_go);
      }
    }
  }
}

void Scene::update_game_objects_states(){
  for(auto go : objects){
    go->update_state();
  }
}

void Scene::update(){
  Physics *physics = Physics::get_instance();
  physics->act();
  run_collisions();
  update_game_objects_states();
}
