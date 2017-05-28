#include "scene.hpp"
#include <algorithm>

using namespace engine;

bool compare_scene(pair<int, engine::GameObject*> a, pair<int, engine::GameObject*> b){
  return a.first < b.first;
}


void Scene::add_object(int priority, engine::GameObject* object){
  objects.push_back(std::make_pair(priority, object));
  sort(objects.begin(), objects.end(), compare_scene);
}

void Scene::activate_game_object(std::string game_object_name){
  for(auto go : objects){
    if(go.second->name == game_object_name){
      go.second->active_game_object = true;
      EventHandler::add_listener(go.second);
    }
  }
}

void Scene::deactivate_game_object(std::string game_object_name){
  for(auto go : objects){
    if(go.second->name == game_object_name){
      go.second->active_game_object = false;
      EventHandler::remove_listener(go.second);
    }
  }
}
