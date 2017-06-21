#ifndef SCENE_H
#define SCENE_H

#include "SDL2basics.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
#include "game_object.hpp"
#include "event_handler.hpp"

namespace engine {

  class Scene {
    private:
      void run_collisions(void);
      void update_game_objects_states();

    public:
      std::vector<engine::GameObject*> objects;

      Scene(){};
      ~Scene(){};

      void add_object(engine::GameObject* object);
      virtual void draw(){};
      virtual void load(){};
      virtual void free(){};
      void activate_game_object(std::string name);
      void deactivate_game_object(std::string name);
      void deactivate_scene();
      void update();
  };
}

#endif
