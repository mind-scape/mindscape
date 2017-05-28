#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
#include "game_object.hpp"
#include "event_handler.hpp"

namespace engine{

  class Scene {
    public:
      std::vector<std::pair<int, engine::GameObject*> > objects;

      Scene(){};
      ~Scene(){};

      void add_object(int priority, engine::GameObject* object);
      virtual void draw(){};
      virtual void load(){};
      virtual void free(){};
      void activate_game_object(std::string name);
      void deactivate_game_object(std::string name);
  };

}

#endif
