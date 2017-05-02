#include "scene.hpp"

using namespace engine;

void Scene::add_object(std::string name, engine::GameObject* object){
  objects.insert({name, object});
}
