#include "scene.hpp"

using namespace engine;

void Scene::add_object(std::string name, engine::GameObject* object){
  objects.insert({name, object});
}

void Scene::activate_game_object(std::string game_object_name){
  objects[game_object_name]->active_game_object = true;
  EventHandler::add_listener(objects[game_object_name]);
}

void Scene::deactivate_game_object(std::string game_object_name){
  objects[game_object_name]->active_game_object = false;
  EventHandler::remove_listener(objects[game_object_name]);
}
