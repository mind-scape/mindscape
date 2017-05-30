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

bool Scene::check_collision(SDL_Rect a, SDL_Rect b){
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  //Calculate the sides of rect A
  left_a = a.x;
  right_a = a.x + a.w;
  top_a = a.y;
  bottom_a = a.y + a.h;

  //Calculate the sides of rect B
  left_b = b.x;
  right_b = b.x + b.w;
  top_b = b.y;
  bottom_b = b.y + b.h;

  if(bottom_a <= top_b){
    return false;
  }

  if(top_a >= bottom_b){
    return false;
  }

  if(right_a <= left_b){
    return false;
  }

  if(left_a >= right_b){
    return false;
  }
  return true;
}


void run_collisions(){
  for(auto go : objects){
    if(go->collidable){
      for(auto another_go : objects){
        if(!equals(go, another_go) && check_collision(go, another_go)){

        }
      }
    }
  }
}
