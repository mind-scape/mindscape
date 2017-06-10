#include "scene.hpp"
#include <algorithm>

using namespace engine;

bool compare_scene(engine::GameObject* a, GameObject* b){
  return a->priority < b->priority;
}

void Scene::add_object(engine::GameObject* object){
  objects.push_back(object);
  sort(objects.begin(), objects.end(), compare_scene);
}

void Scene::activate_game_object(std::string game_object_name){
  for(auto go : objects){
    if(go->name == game_object_name){
      go->active_game_object = true;
      EventHandler::add_listener(go);
    }
  }
}

void Scene::deactivate_game_object(std::string game_object_name){
  for(auto go : objects){
    if(go->name == game_object_name){
      go->active_game_object = false;
      EventHandler::remove_listener(go);
    }
  }
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

void Scene::update(unsigned delta){
  for(auto go : objects){
    go->update(delta);
  }
}
